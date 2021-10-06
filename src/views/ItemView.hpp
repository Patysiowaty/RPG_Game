#ifndef ITEMVIEW_HPP
#define ITEMVIEW_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../item_types/Item.hpp"
#include "../ui_elements/Window.hpp"
#include "../ui_elements/Label.hpp"

class ItemTipView : public Window {
 public:
  explicit ItemTipView(const std::shared_ptr<Item> &item, Window *parent_wnd = nullptr) : parent_wnd_{parent_wnd} {
	FillData(item);
	Window::SetSize({200, 250});
	Window::SetFillColor({128, 128, 128, 180});
	Window::SetOutlineColor({0, 0, 0, 180});
	Window::SetOutlineThickness(1.f);
	item_name_.SetRelativePosition({100, 10});
	item_name_.SetTextSize(20);
	SetLabels();
  }

  void Update(float delta_time) override {
	Window::Update(delta_time);

  }

  void SetPosition(const sf::Vector2f &new_position) override {
	Window::SetPosition(new_position);
	item_name_.SetPosition(new_position);
	for (auto &label: stats_labels_)
	  label.SetPosition(new_position);
  }

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
	Window::draw(target, states);
	target.draw(item_name_, states);
	for (auto &label: stats_labels_)
	  target.draw(label, states);
  }

 private:
  void FillData(const std::shared_ptr<Item> &item) {
	const auto &kItemName = item->GetItemName();
	item_name_.SetTextString(kItemName);
	const auto &kItemAttributesList = item->GetAttributes();
	for (auto &attribute: kItemAttributesList) {
	  if (attribute.GetValue() == 0) continue;
	  auto label_text = ParseAttribute(attribute.GetType());
	  if (label_text.empty()) continue;
	  label_text += std::to_string(attribute.GetValue());
	  stats_labels_.emplace_back(label_text);
	}

	const auto &kItemStatisticsList = item->GetStatistics();
	for (auto &statistic: kItemStatisticsList) {
	  if (statistic.GetValue() == 0) continue;
	  auto label_text = ParseStatistic(statistic.GetType());
	  if (label_text.empty()) continue;
	  label_text += std::to_string(statistic.GetValue());
	  stats_labels_.emplace_back(label_text);
	}
  }

  void SetLabels() {
	sf::Vector2f start_pos{50, 30};
	sf::Vector2f relative_pos_modifier{0, 15.f};
	for (auto &label: stats_labels_) {
	  label.SetTextSize(18);
	  label.SetRelativePosition(start_pos);
	  start_pos += relative_pos_modifier;
	}

  }

  std::string ParseAttribute(AttributeType type) {
	switch (type) {
	  case AttributeType::kStrength:
		return "Strength: ";
	  case AttributeType::kDexterity:
		return "Dexterity: ";
	  case AttributeType::kVitality:
		return "Vitality: ";
	  case AttributeType::kIntelligence:
		return "Intelligence: ";
	  default:
		return "";
	}
  }
  std::string ParseStatistic(StatisticType type) {
	switch (type) {
	  case StatisticType::kAttack:
		return "Attack: ";
	  case StatisticType::kMagicAttack:
		return "Magic attack: ";
	  case StatisticType::kHealth:
		return "Health: ";
	  case StatisticType::kArmor:
		return "Armor: ";
	  case StatisticType::kStamina:
		return "Stamina: ";
	  case StatisticType::kMana:
		return "Mana: ";
	  case StatisticType::kMagicResistance:
		return "Magic resistance: ";
	  case StatisticType::kEvadeRatio:
		return "Evade ratio: ";
	  case StatisticType::kCriticalStrikeRatio:
		return "Critical strike ratio: ";
	  case StatisticType::kCriticalStrikeForce:
		return "Critical strike force: ";
	  default:
		return "";
	}
  }

 private:
  Window *parent_wnd_{nullptr};
  Label item_name_;
  std::vector<Label> stats_labels_;
};

class ItemView : public Window {
 public:
  explicit ItemView(const std::shared_ptr<Item> &item);

  void FillData(const std::shared_ptr<Item> &item);
  void Move(const sf::Vector2f &offset) override;
  void SetPosition(const sf::Vector2f &new_position) override;
  void Update(float delta_time) override;
  std::uint32_t GetItemId() const { return item_id_; }

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  std::uint32_t item_id_;
  ItemTipView item_tip_view_;
};

#endif //ITEMVIEW_HPP

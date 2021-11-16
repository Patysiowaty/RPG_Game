#include "ItemTipView.hpp"
ItemTipView::ItemTipView() {
  SetSize({200, 250});
  SetFillColor({128, 128, 128, 180});
  SetOutlineColor({0, 0, 0, 180});
  SetOutlineThickness(1.f);
}

ItemTipView::ItemTipView(const std::shared_ptr<Item> &item) {
  SetSize({200, 250});
  SetFillColor({0, 0, 0, 150});
  SetOutlineColor({0, 0, 0, 180});
  SetOutlineThickness(2.f);
  FillData(item);
}

void ItemTipView::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);
  for (auto &label: stats_labels_)
	label.SetPosition(new_position);
}

void ItemTipView::FillData(const std::shared_ptr<Item> &item) {
  const auto &kItemName = item->GetItemName();
  stats_labels_.emplace_back(kItemName);

  const auto kItemRarity = item->GetItemRarity();
  stats_labels_.emplace_back(ParseRarities(kItemRarity));

  const auto &kItemAttributesList = item->GetAttributes();
  const auto &kItemStatisticsList = item->GetStatistics();
  stats_labels_.reserve(kItemAttributesList.size() + kItemStatisticsList.size());

  for (auto &attribute: kItemAttributesList) {
	const auto kLabelText = ParseAttribute(attribute);
	if (kLabelText.empty()) continue;
	stats_labels_.emplace_back(kLabelText);
  }

  for (auto &statistic: kItemStatisticsList) {
	const auto kLabelText = ParseStatistic(statistic);
	if (kLabelText.empty()) continue;
	stats_labels_.emplace_back(kLabelText);
  }

  const auto kItemLevelReq = item->GetLevelRequirement();
  stats_labels_.emplace_back("Level requires " + std::to_string(kItemLevelReq));

  SetLabels();
}

void ItemTipView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  Window::draw(target, states);
  for (auto &label: stats_labels_)
	target.draw(label, states);
}

void ItemTipView::SetLabels() {
  const sf::Vector2f kLabelSize = {200.f, 0.f};

  auto &item_name = stats_labels_.at(0);
  item_name.SetRelativePosition({0, 10.f});
  item_name.SetAlign(TextAlign::kCenter);
  item_name.SetFillColor(sf::Color::Transparent);
  item_name.SetTextColor(sf::Color::White);
  item_name.SetTextSize(20);
  item_name.SetSize(kLabelSize);

  auto &item_rarity = stats_labels_.at(1);
  item_rarity.SetRelativePosition({0, 25.f});
  item_rarity.SetAlign(TextAlign::kCenter);
  item_rarity.SetFillColor(sf::Color::Transparent);
  item_rarity.SetTextColor(rarity_color_);
  item_rarity.SetTextSize(18);
  item_rarity.SetSize(kLabelSize);

  sf::Vector2f start_pos{5, 40};
  sf::Vector2f relative_pos_modifier{0, 15.f};

  std::for_each(stats_labels_.begin() + 2, stats_labels_.end(),
				[&start_pos, kLabelSize, relative_pos_modifier](Label &label) {
				  label.SetTextSize(18);
				  label.SetRelativePosition(start_pos);
				  label.SetFillColor(sf::Color::Transparent);
				  label.SetSize(kLabelSize);
				  label.SetTextColor(sf::Color::White);
				  label.SetTextOutlineThickness(0);
				  start_pos += relative_pos_modifier;
				});
}

std::string ItemTipView::ParseAttribute(const Attribute &attribute) {
  const auto kType = attribute.GetType();
  std::string text;
  switch (kType) {
	case AttributeType::kStrength:
	  text = "Strength";
	  break;
	case AttributeType::kDexterity:
	  text = "Dexterity";
	  break;
	case AttributeType::kVitality:
	  text = "Vitality";
	  break;
	case AttributeType::kIntelligence:
	  text = "Intelligence";
	  break;
	default:
	  return std::string{};
  }
  text += " +" + std::to_string(attribute.GetValue());
  return text;
}

std::string ItemTipView::ParseStatistic(const Statistic &statistic) {
  const auto kType = statistic.GetType();

  std::string text;
  switch (kType) {
	case StatisticType::kAttack:
	  text = "Attack";
	  break;
	case StatisticType::kMagicAttack:
	  text = "Magic attack";
	  break;
	case StatisticType::kHealth:
	  text = "Health";
	  break;
	case StatisticType::kArmor:
	  text = "Armor";
	  break;
	case StatisticType::kStamina:
	  text = "Stamina";
	  break;
	case StatisticType::kMana:
	  text = "Mana";
	  break;
	case StatisticType::kMagicResistance:
	  text = "Magic resistance";
	  break;
	case StatisticType::kEvadeRatio:
	  text = "Evade ratio";
	  break;
	case StatisticType::kCriticalStrikeRatio:
	  text = "Critical strike ratio";
	  break;
	case StatisticType::kCriticalStrikeForce:
	  text = "Critical strike force";
	  break;
	default:
	  return std::string{};
  }

  text += " +" + std::to_string(statistic.GetValue());
  return text;
}

std::string ItemTipView::ParseRarities(ItemRarity rarity) {
  switch (rarity) {
	case ItemRarity::kCommon:
	  rarity_color_ = sf::Color{128, 128, 128, 255};
	  return "Common";
	case ItemRarity::kRare:
	  rarity_color_ = sf::Color::Blue;
	  return "Rare";
	case ItemRarity::kUnique:
	  rarity_color_ = sf::Color::Yellow;
	  return "Unique";
	case ItemRarity::kEpic:
	  rarity_color_ = sf::Color::Red;
	  return "Epic";
	case ItemRarity::kLegendary:
	  rarity_color_ = sf::Color::Green;
	  return "Legendary";
  }
}

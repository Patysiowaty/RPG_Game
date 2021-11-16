#include "PlayerStatsWindow.hpp"
#include "../commands/CloseWindowCommand.hpp"
#include "../commands/ShowMoreStatisticsCommand.hpp"
#include "../commands/ShowLessStatisticsCommand.hpp"
#include "../managers/WindowsManager.hpp"
#include "../commands/ChangePlayerViewAnimation.hpp"
#include <boost/range/adaptor/reversed.hpp>

PlayerStatsWindow::PlayerStatsWindow(PlayerController &player_controller, const std::string &window_name) :
	player_controller_{player_controller}, wnd_name_{window_name} {

}

void PlayerStatsWindow::OnInit() {
  font_.loadFromFile("../resources/fonts/romulus.ttf");
  Window::LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {0, 0, 351, 292});

  draggable_trigger_.setSize({319, 15});
  draggable_trigger_.setPosition({16, 16});

  CreateLabels();
  SetLabels();
  SetValueLabels();
  FillValueLabelsData();
  CreateButtons();
  SetButtons();
  CreateEquipmentSlots();
  SetPlayerView();
  FillEquipmentSlots();
}

void PlayerStatsWindow::Deserialize(const boost::property_tree::ptree &ptree) {
  Window::Deserialize(ptree);
}

void PlayerStatsWindow::Update(float delta_time) {
  Window::Update(delta_time);
  player_view_window_.Update(delta_time);
  for (auto &[type, slot]: equipment_slots_list_) {
	slot.Update(delta_time);
  }

  for (auto&[type, button]: buttons_list_) {
	button.Update(delta_time);
  }
}

void PlayerStatsWindow::Move(const sf::Vector2f &offset) {
  Window::Move(offset);

  wnd_name_.Move(offset);

  for (auto &[type, label]: attribute_text_labels_)
	label.Move(offset);

  for (auto &[type, value_label]: attribute_value_labels_)
	value_label.Move(offset);

  for (auto &[type, label]: statistic_text_labels_)
	label.Move(offset);

  for (auto &[type, value_label]: statistic_value_labels_)
	value_label.Move(offset);

  for (auto &[type, item_view]: equipment_slots_list_)
	item_view.Move(offset);

  for (auto&[type, button]: buttons_list_)
	button.SetPosition(offset);

  character_name_label_.Move(offset);

  player_view_window_.Move(offset);
}

void PlayerStatsWindow::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);

  wnd_name_.SetPosition(new_position);

  for (auto &[type, label]: attribute_text_labels_)
	label.SetPosition(new_position);

  for (auto &[type, value_label]: attribute_value_labels_)
	value_label.SetPosition(new_position);

  for (auto &[type, label]: statistic_text_labels_)
	label.SetPosition(new_position);

  for (auto &[type, value_label]: statistic_value_labels_)
	value_label.SetPosition(new_position);

  for (auto &[type, item_view]: equipment_slots_list_)
	item_view.SetPosition(new_position);

  for (auto&[type, button]: buttons_list_)
	button.SetPosition(new_position);

  character_name_label_.SetPosition(new_position);

  player_view_window_.SetPosition(new_position);
}

void PlayerStatsWindow::OnChildrenWindowEvent(Window *sender, WindowEvent event_type) {
  Window::OnChildrenWindowEvent(sender, event_type);

  for (const auto&[type, slot]: equipment_slots_list_) {
	if (&slot == sender && event_type == WindowEvent::kLeftMouseClick) {
	  RemoveItem(type);
	}
  }
}

void PlayerStatsWindow::OpenWindow() {
  Window::SetVisible(true);
  FillEquipmentSlots();
  FillValueLabelsData();
}

void PlayerStatsWindow::CloseWindow() {
  Window::SetVisible(false);
}

bool PlayerStatsWindow::IsOpen() const {
  return Window::IsVisible();
}

void PlayerStatsWindow::RegisterManager(WindowsManager *windows_manager) {
  windows_manager_ = windows_manager;
}

void PlayerStatsWindow::ReloadData() {
  if (!Window::IsVisible()) return;
  FillEquipmentSlots();
  FillValueLabelsData();
}

void PlayerStatsWindow::RemoveItem(ItemType item_type) {
  if (player_controller_.TakeOffItem(item_type)) {
	equipment_slots_list_.at(item_type).TakeOutItem();
	player_view_window_.TakeOffItem(item_type);
	windows_manager_->ReloadWindowsData({WindowTypes::kInventory, WindowTypes::kPlayerStatistics});
  }
}

void PlayerStatsWindow::ShowMoreStats() {
  auto &scroll_down_btn = buttons_list_.at(ButtonTypes::kShowMore);
  if (!scroll_down_btn.IsActive()) return;

  InvertStatisticsVisibility();

  scroll_down_btn.Deactivate();
  buttons_list_.at(ButtonTypes::kShowLess).Activate();
}

void PlayerStatsWindow::ShowLessStats() {
  auto &scroll_up_btn = buttons_list_.at(ButtonTypes::kShowLess);
  if (!scroll_up_btn.IsActive()) return;

  InvertStatisticsVisibility();

  scroll_up_btn.Deactivate();
  buttons_list_.at(ButtonTypes::kShowMore).Activate();
}

void PlayerStatsWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!Window::IsVisible()) return;
  Window::draw(target, states);

  target.draw(wnd_name_, states);

  for (const auto &[type, label]: attribute_text_labels_)
	target.draw(label, states);

  for (const auto &[type, value_label]: attribute_value_labels_)
	target.draw(value_label, states);

  for (const auto &[type, label]: statistic_text_labels_)
	target.draw(label, states);

  for (const auto &[type, value_label]: statistic_value_labels_)
	target.draw(value_label, states);

  target.draw(character_name_label_, states);

  target.draw(player_view_window_, states);

  for (auto&[type, button]: buttons_list_)
	target.draw(button, states);

  for (auto &[type, item_view]: boost::adaptors::reverse(equipment_slots_list_))
	target.draw(item_view, states);
}

void PlayerStatsWindow::CreateLabels() {
  const std::vector<std::pair<StatisticType, std::string>> kStatisticLabelsWithDesc{
	  {StatisticType::kAttack, "Attack"}, {StatisticType::kMagicAttack, "Magic attack"},
	  {StatisticType::kHealth, "Health"}, {StatisticType::kArmor, "Armor"}, {StatisticType::kStamina, "Stamina"},
	  {StatisticType::kMana, "Mana"}, {StatisticType::kMagicResistance, "Magic res."},
	  {StatisticType::kEvadeRatio, "Evade ratio"}, {StatisticType::kCriticalStrikeRatio, "Crit. ratio"},
	  {StatisticType::kCriticalStrikeForce, "Crit. force"}};

  const std::vector<std::pair<AttributeType, std::string>>
	  kAttributeLabelsWithDesc{{AttributeType::kStrength, "Strength"}, {AttributeType::kDexterity, "Dexterity"},
							   {AttributeType::kVitality, "Vitality"}, {AttributeType::kIntelligence, "Intelligence"}};

  for (const auto &attr_with_desc: kAttributeLabelsWithDesc) {
	attribute_text_labels_.emplace(attr_with_desc.first, attr_with_desc.second);
	attribute_value_labels_.emplace(attr_with_desc.first, "");
  }

  for (const auto &stats_with_desc: kStatisticLabelsWithDesc) {
	statistic_text_labels_.emplace(stats_with_desc.first, stats_with_desc.second);
	statistic_value_labels_.emplace(stats_with_desc.first, "");
  }

}

void PlayerStatsWindow::SetLabels() {
  sf::Vector2f text_label_pos{193.f, 41.f};
  const sf::Vector2f kHeightOffset{0.f, 22.f};
  const sf::Vector2f kWidthOffset{114.f, 0};
  const int kMaxStatsLabels{5};

  int counter{0};
  for (auto&[type, label]: attribute_text_labels_) {
	const auto next_pos = text_label_pos + sf::Vector2f{0, kHeightOffset.y * counter};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {50, 293, 112, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	label.SetSize({106, 14});
	label.SetMarginLeft(7.f);
	++counter;
  }

  counter = 0;
  for (auto&[type, label]: attribute_value_labels_) {
	const auto next_pos = text_label_pos + sf::Vector2f{kWidthOffset.x, kHeightOffset.y * counter};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {164, 293, 26, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	label.SetAlign(TextAlign::kCenter);
	++counter;
  }

  text_label_pos += sf::Vector2f{0, 10.f};

  const int kTemp = counter;
  int j = counter;

  for (auto&[type, label]: statistic_text_labels_) {
	bool visible{true};

	if (counter >= (kTemp + kMaxStatsLabels)) {
	  visible = false;
	  if (j >= kTemp + kMaxStatsLabels)
		j = kTemp;
	}

	const auto next_pos = text_label_pos + sf::Vector2f{0, kHeightOffset.y * j};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {50, 293, 112, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	label.SetSize({106, 14});
	label.SetVisible(visible);
	label.SetMarginLeft(7.f);
	++counter;
	++j;
  }

  counter = kTemp;
  j = kTemp;

  for (auto&[type, label]: statistic_value_labels_) {
	bool visible{true};

	if (counter >= (kTemp + kMaxStatsLabels)) {
	  visible = false;
	  if (j >= kTemp + kMaxStatsLabels)
		j = kTemp;
	}

	const auto next_pos = text_label_pos + sf::Vector2f{kWidthOffset.x, kHeightOffset.y * j};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {164, 293, 26, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	label.SetVisible(visible);
	label.SetAlign(TextAlign::kCenter);
	++counter;
	++j;
  }

  character_name_label_.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {191, 293, 172, 20});
  character_name_label_.SetSize({172, 20});
  character_name_label_.SetRelativePosition({13, 36});
  character_name_label_.SetAlign(TextAlign::kCenter);
  character_name_label_.SetPosition(Window::GetRectangleShape().getPosition());

  wnd_name_.SetRelativePosition({16, 16});
  wnd_name_.SetSize({319, 15});
  wnd_name_.SetAlign(TextAlign::kCenter);
  wnd_name_.SetPosition(Window::GetRectangleShape().getPosition());
}

void PlayerStatsWindow::SetValueLabels() {
  const auto &kPlayer = player_controller_.GetPlayer();

  const auto &kAttrList = kPlayer.GetPlayerAttributes().GetAttributesList();

  for (const auto &kAttr: kAttrList) {
	const auto kType = kAttr->GetType();
	auto &label = attribute_value_labels_.at(kType);
	label.SetTextColor(sf::Color::White);
	label.SetTextOutlineColor({130, 130, 130, 125});
	label.SetTextOutlineThickness(1.f);
  }

  const auto &kStatList = kPlayer.GetCharacterStatistics().GetStatisticsList();

  for (const auto &kStat: kStatList) {
	const auto kType = kStat->GetType();
	auto &label = statistic_value_labels_.at(kType);
	label.SetTextColor(sf::Color::White);
	label.SetTextOutlineColor({130, 130, 130, 125});
	label.SetTextOutlineThickness(1.f);
  }
}

void PlayerStatsWindow::FillValueLabelsData() {
  const auto &kPlayer = player_controller_.GetPlayer();

  const auto &kAttrList = kPlayer.GetPlayerAttributes().GetAttributesList();

  for (const auto &kAttr: kAttrList) {
	const auto kType = kAttr->GetType();
	const auto kValue = kAttr->GetValue();
	auto &label = attribute_value_labels_.at(kType);
	label.SetTextString(std::to_string(kValue));
  }

  const auto &kStatList = kPlayer.GetCharacterStatistics().GetStatisticsList();

  for (const auto &kStat: kStatList) {
	const auto kType = kStat->GetType();
	const auto kValue = kStat->GetMaxValue();
	auto &label = statistic_value_labels_.at(kType);
	label.SetTextString(std::to_string(kValue));
  }

  const auto &kName = kPlayer.GetName();
  const auto &kLevel = kPlayer.GetPlayerLevel().GetLevel();

  std::stringstream ss;
  ss << kName << ", " << kLevel << "lvl";

  character_name_label_.SetTextString(ss.str());
}

void PlayerStatsWindow::CreateEquipmentSlots() {
  const sf::Vector2f kStartPos{13, 58};
  const sf::Vector2f kHeightOffset{0, 38};
  const sf::Vector2f kWidthOffset{136, 0};

  const auto kEqSize = static_cast<int>(ItemType::kSize) - 1;
  for (int i = 0; i < kEqSize; ++i) {
	const auto type = ItemType(i);
	equipment_slots_list_.emplace(type, this);
	const auto width_mod = i < (kEqSize / 2) ? 0 : 1;
	const auto height_mod = i % (kEqSize / 2);
	sf::Vector2f next_pos = sf::Vector2f{kWidthOffset.x * width_mod, kHeightOffset.y * height_mod} + kStartPos;
	equipment_slots_list_.at(type).SetRelativePosition(next_pos);
	equipment_slots_list_.at(type).SetPosition(Window::GetRectangleShape().getPosition());
	equipment_slots_list_.at(type).LoadWindowTexture("../resources/graphics/character_stats_sprite.png",
													 {97, 314, 36, 36});
  }
}

void PlayerStatsWindow::FillEquipmentSlots() {
  auto &player = player_controller_.GetPlayer();
  for (auto&[type, slot]: equipment_slots_list_) {
	const auto &item = player.GetPlayerEquipment().GetItemAtSlot(type);
	if (item) {
	  slot.PutItem(std::make_unique<ItemView>(item));
	  player_view_window_.EquipItem(item);
	}

  }
}

void PlayerStatsWindow::CreateButtons() {
  const auto kSize = static_cast<int>(ButtonTypes::kSize);
  for (int i = 0; i < kSize; ++i) {
	const auto kType = ButtonTypes(i);
	buttons_list_.emplace(kType, this);
	auto &button = buttons_list_.at(kType);
	if (kType == ButtonTypes::kCloseButton)
	  button.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {134, 314, 10, 10});
	else if (kType == ButtonTypes::kShowLess || kType == ButtonTypes::kPreviousViewAnimation)
	  button.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {0, 293, 24, 24});
	else
	  button.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {25, 293, 24, 24});
  }

}

void PlayerStatsWindow::SetButtons() {
  auto &close_btn = buttons_list_.at(ButtonTypes::kCloseButton);
  close_btn.AddCommand(CommandInvoker::kLeftMouseButtonClick, std::make_unique<CloseWindowCommand>(*this));
  close_btn.SetRelativePosition({323, 18});
  close_btn.SetPosition(Window::GetRectangleShape().getPosition());

  auto &previous_anim_btn = buttons_list_.at(ButtonTypes::kPreviousViewAnimation);
  previous_anim_btn.SetRelativePosition({69, 181});
  previous_anim_btn.SetPosition(Window::GetRectangleShape().getPosition());
  previous_anim_btn.AddCommand(CommandInvoker::kLeftMouseButtonClick,
							   std::make_unique<ChangePlayerViewAnimation>(player_view_window_,
																		   DirectionCommand::kBack));

  auto &next_anim_btn = buttons_list_.at(ButtonTypes::kNextViewAnimation);
  next_anim_btn.SetRelativePosition({107, 181});
  next_anim_btn.SetPosition(Window::GetRectangleShape().getPosition());
  next_anim_btn.AddCommand(CommandInvoker::kLeftMouseButtonClick,
						   std::make_unique<ChangePlayerViewAnimation>(player_view_window_, DirectionCommand::kNext));

  auto &less_stats_btn = buttons_list_.at(ButtonTypes::kShowLess);
  less_stats_btn.SetRelativePosition({237, 249});
  less_stats_btn.SetPosition(Window::GetRectangleShape().getPosition());
  less_stats_btn.AddCommand(CommandInvoker::kLeftMouseButtonClick, std::make_unique<ShowLessStatisticsCommand>(*this));
  less_stats_btn.Deactivate();

  auto &more_stats_btn = buttons_list_.at(ButtonTypes::kShowMore);
  more_stats_btn.SetRelativePosition({270, 249});
  more_stats_btn.SetPosition(Window::GetRectangleShape().getPosition());
  more_stats_btn.AddCommand(CommandInvoker::kLeftMouseButtonClick, std::make_unique<ShowMoreStatisticsCommand>(*this));

}

void PlayerStatsWindow::SetPlayerView() {
  player_view_window_.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {0, 318, 96, 150});
  player_view_window_.SetRelativePosition(sf::Vector2f{51, 58});
  player_view_window_.SetPosition(Window::GetRectangleShape().getPosition());
  player_view_window_.SetRelativeViewPosition({67, 101});
  player_view_window_.SetPosition(Window::GetRectangleShape().getPosition());
}

void PlayerStatsWindow::InvertStatisticsVisibility() {
  for (auto &[stat, label]: statistic_text_labels_) {
	label.SetVisible(!label.IsVisible());
  }

  for (auto &[stat, label]: statistic_value_labels_) {
	label.SetVisible(!label.IsVisible());
  }
}


#include "PlayerStatsWindow.hpp"
#include "../commands/CloseWindowCommand.hpp"
#include "../managers/WindowsManager.hpp"
#include <boost/range/adaptor/reversed.hpp>

PlayerStatsWindow::PlayerStatsWindow(PlayerController &player_controller, const std::string &window_name) :
	player_controller_{player_controller}, wnd_name_{window_name}, close_button_{this} {
}

void PlayerStatsWindow::Deserialize(const boost::property_tree::ptree &ptree) {
  Window::Deserialize(ptree);
}

void PlayerStatsWindow::Update(float delta_time) {
  Window::Update(delta_time);
  close_button_.Update(delta_time);
  player_view_window_.Update(delta_time);
  for (auto &[type, slot]: equipment_slots_list_) {
	slot.Update(delta_time);
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

  for (auto &[type, item_view]: boost::adaptors::reverse(equipment_slots_list_))
	target.draw(item_view, states);

  target.draw(character_name_label_, states);

  target.draw(player_view_window_, states);
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

const sf::Vector2f &PlayerStatsWindow::GetWindowSize() const {
  return Window::GetRectangleShape().getSize();
}

void PlayerStatsWindow::OnInit() {
  font_.loadFromFile("../resources/fonts/romulus.ttf");
  Window::LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {0, 0, 351, 292});

  draggable_trigger_.setSize({319, 15});
  draggable_trigger_.setPosition({16, 16});

  CreateLabels();
  SetLabels();
  SetValueLabelsData();
  FillValueLabelsData();
  SetButtons();
  CreateEquipmentSlots();
  SetPlayerView();
  FillEquipmentSlots();
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

void PlayerStatsWindow::SetLabels() {
  sf::Vector2f text_label_pos{193.f, 41.f};
  const sf::Vector2f kHeightOffset{0.f, 22.f};
  const sf::Vector2f kWidthOffset{114.f, 0};
  const int kMaxStatsLabels{5};

  int i{0};
  for (auto&[type, label]: attribute_text_labels_) {
	const auto next_pos = text_label_pos + sf::Vector2f{0, kHeightOffset.y * i};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {50, 293, 112, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	++i;
  }

  i = 0;
  for (auto&[type, label]: attribute_value_labels_) {
	const auto next_pos = text_label_pos + sf::Vector2f{kWidthOffset.x, kHeightOffset.y * i};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {164, 293, 26, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	++i;
  }

  text_label_pos += sf::Vector2f{0, 12.f};

  const int kTemp = i;
  int j = i;
  for (auto&[type, label]: statistic_text_labels_) {
	bool visible{true};

	if (i >= (kTemp + kMaxStatsLabels)) {
	  visible = false;
	  j = kTemp;
	}

	const auto next_pos = text_label_pos + sf::Vector2f{0, kHeightOffset.y * j};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {50, 293, 112, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	label.SetVisible(visible);
	++i;
	++j;
  }

  i = kTemp;
  j = kTemp;

  for (auto&[type, label]: statistic_value_labels_) {
	bool visible{true};

	if (i >= (kTemp + kMaxStatsLabels)) {
	  visible = false;
	  j = kTemp;
	}

	const auto next_pos = text_label_pos + sf::Vector2f{kWidthOffset.x, kHeightOffset.y * j};
	label.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {164, 293, 26, 20});
	label.SetRelativePosition(next_pos);
	label.SetPosition(Window::GetRectangleShape().getPosition());
	label.SetVisible(visible);
	++i;
	++j;
  }

  character_name_label_.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {191, 293, 172, 20});
  character_name_label_.SetSize({172, 20});
  character_name_label_.SetRelativePosition({13, 36});
  character_name_label_.SetPosition(Window::GetRectangleShape().getPosition());

  wnd_name_.SetRelativePosition({16, 16});
  wnd_name_.SetSize({319, 15});
  wnd_name_.SetColor(sf::Color::Transparent);
  wnd_name_.SetPosition(Window::GetRectangleShape().getPosition());
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

void PlayerStatsWindow::SetButtons() {
  close_button_.AddCommand(CommandInvoker::kLeftMouseButtonClick, std::make_unique<CloseWindowCommand>(*this));
  close_button_.SetRelativePosition({323, 18});
  close_button_.SetPosition(Window::GetRectangleShape().getPosition());
  close_button_.SetSize({10, 10});
}

void PlayerStatsWindow::SetPlayerView() {
  player_view_window_.SetRelativePosition(sf::Vector2f{51, 58});
  player_view_window_.LoadWindowTexture("../resources/graphics/character_stats_sprite.png", {0, 319, 96, 150});
  player_view_window_.SetPosition(Window::GetRectangleShape().getPosition());
  player_view_window_.SetRelativeViewPosition({67, 101});
  player_view_window_.SetPosition(Window::GetRectangleShape().getPosition());
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

void PlayerStatsWindow::SetValueLabelsData() {
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

  character_name_label_.SetTextColor(sf::Color::Black);
  character_name_label_.SetTextOutlineColor({130, 130, 130, 125});
  character_name_label_.SetTextOutlineThickness(1.f);
}

void PlayerStatsWindow::RemoveItem(ItemType item_type) {
  if (player_controller_.TakeOffItem(item_type)) {
	equipment_slots_list_.at(item_type).TakeOutItem();
	player_view_window_.TakeOffItem(item_type);
	windows_manager_->ReloadWindowsData({WindowTypes::kInventory, WindowTypes::kPlayerStatistics});
  }
}

void PlayerStatsWindow::RegisterManager(WindowsManager *windows_manager) {
  windows_manager_ = windows_manager;
}

void PlayerStatsWindow::ReloadData() {
  if (!Window::IsVisible()) return;
  FillEquipmentSlots();
  FillValueLabelsData();
}


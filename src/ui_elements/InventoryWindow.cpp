#include "InventoryWindow.hpp"
#include "../managers/InputManager.hpp"
#include "../commands/CloseWindowCommand.hpp"

InventoryWindow::InventoryWindow(Player &player, const std::string &wnd_name) : player_{player},
																				window_name_text_{wnd_name, font_},
																				close_btn_{this},
																				next_tab_btn_{this},
																				previous_tab_btn_{this} {
  inventory_sprite_.loadFromFile("../resources/graphics/inventory.png", kInventoryWndSpritePosition);
  font_.loadFromFile("../resources/fonts/romulus.ttf");

  Window::SetWindowTexture(&inventory_sprite_, kInventoryWndSpritePosition);
  CreateSlots();
  PlaceSlots();
  PlaceItems();
  InitializeWndComponents();
  InitializeButtons();
  close_btn_.AddCommand(CommandInvoker::kLeftMouseButtonClick, std::make_unique<CloseWindowCommand>(*this));
}

void InventoryWindow::Deserialize(const boost::property_tree::ptree &ptree) {
  Window::Deserialize(ptree);
}

void InventoryWindow::Update(float delta_time) {
  Window::Update(delta_time);
  close_btn_.Update(delta_time);

  if (InputManager::IsKeyReleased(sf::Keyboard::I)) {
	if (IsVisible())
	  std::make_unique<CloseWindowCommand>(*this)->Execute();
	else
	  OpenWindow();
  }
}

void InventoryWindow::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
  window_name_text_.move(offset);
  close_btn_.Move(offset);
  draggable_trigger_.move(offset);
  for (auto&[first, second]: items_slots_) {
	second.Move(offset);
  }
  for (auto &tab: inventory_tabs_)
	tab.Move(offset);
}

void InventoryWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!IsVisible()) return;
  Window::draw(target, states);
  for (auto&[first, second]: items_slots_)
	target.draw(second);
  target.draw(window_name_text_);
  target.draw(close_btn_);
//  target.draw(draggable_trigger_);
  target.draw(next_tab_btn_);
  target.draw(previous_tab_btn_);
  for (auto &tab: inventory_tabs_) {
	target.draw(tab);
  }
}

void InventoryWindow::OpenWindow() {
  Window::SetVisible(true);
}

void InventoryWindow::CloseWindow() {
  Window::SetVisible(false);
}

void InventoryWindow::CreateSlots() {
  for (int i = 0; i < kColumnItemCount; ++i) {
	for (int j = 0; j < kRowItemCount; ++j) {
	  const auto kSlotIndex = SlotIndex{i, j};
	  items_slots_.emplace(kSlotIndex, ItemSlot{});
	  items_slots_.at(kSlotIndex).LoadWindowTexture("../resources/graphics/inventory.png", kSlotSizeSpritePosition);
	}
  }
}

void InventoryWindow::PlaceSlots() {
  const auto kOffset = sf::Vector2f{38, 38};
  sf::Vector2f start_pos{13, 35};

  for (auto&[first, second]: items_slots_) {
	sf::Vector2f slot_pos{static_cast<float>(first.second) * kOffset.x, static_cast<float>(first.first) * kOffset.y};
	slot_pos += start_pos;
	second.SetPosition(slot_pos);
  }
}

void InventoryWindow::PlaceItems() {
  const auto &items = player_.GetPlayerInventory().GetInventory();
  int i = 0;
  for (int j = 0; j < items.size(); ++j) {
	const auto index = j % kRowItemCount;
	if (j != 0 && index == 0) ++i;
	if (items.at(i)) {
	  SlotIndex slot_index{i, index};
	  PlaceItem(items.at(i), slot_index);
	}
  }
}

void InventoryWindow::RemoveItems() {

}

void InventoryWindow::InitializeWndComponents() {
  draggable_trigger_.setSize(sf::Vector2f{192, 14});
  draggable_trigger_.setPosition(sf::Vector2f{11, 11} + Window::GetRectangleShape().getPosition());
  draggable_trigger_.setFillColor(sf::Color::Transparent);

  window_name_text_.setCharacterSize(20);
  window_name_text_.setFillColor(sf::Color::White);
  //window_name_text_.setOutlineColor({0, 0, 0, 100});
  //window_name_text_.setOutlineThickness(1.f);
  Window::CenterTextToFit(window_name_text_, draggable_trigger_);

  inventory_tabs_.reserve(PlayerInventory::GetMaxTabs());
}

void InventoryWindow::InitializeButtons() {
  close_btn_.SetSize(sf::Vector2f{static_cast<float>(kCloseButtonSpritePosition.width),
								  static_cast<float>(kCloseButtonSpritePosition.height)});

  close_btn_.LoadWindowTexture("../resources/graphics/inventory.png", kCloseButtonSpritePosition);

  close_btn_.SetPosition(sf::Vector2f{190.f, 13.f} + Window::GetRectangleShape().getPosition());

  sf::Vector2f tab_pos{56, 301};
  sf::Vector2f tab_size{24, 24};
  auto tab_offset = sf::Vector2f{2 + tab_size.x, 0};

  for (int i = 0; i < PlayerInventory::GetMaxTabs(); ++i) {
	inventory_tabs_.emplace_back(Button{this});
	inventory_tabs_.at(i).LoadWindowTexture("../resources/graphics/inventory.png", {214, 90, 24, 24});
	inventory_tabs_.at(i).LoadFont("../resources/fonts/romulus.ttf");
	inventory_tabs_.at(i).SetTextString(std::to_string(i + 1), {185, 122, 87, 255}, 20);
	inventory_tabs_.at(i).SetTextOutline({77, 48, 32, 255}, 1.f);
	inventory_tabs_.at(i).SetPosition(tab_pos + sf::Vector2f{tab_offset.x * static_cast<float>(i), tab_offset.y});
  }

  previous_tab_btn_.LoadWindowTexture("../resources/graphics/inventory.png", {214, 64, 24, 24});
  previous_tab_btn_.SetPosition({13, 300});

  next_tab_btn_.LoadWindowTexture("../resources/graphics/inventory.png", {214, 38, 24, 24});
  next_tab_btn_.SetPosition({177, 300});
}

void InventoryWindow::RemoveItem(const SlotIndex &slot_index) {
  items_slots_.at(slot_index).TakeOutItem();
}

void InventoryWindow::PlaceItem(const std::shared_ptr<Item> &item, const SlotIndex &slot_index) {
  if (items_slots_.at(slot_index).IsEmpty())
	throw std::invalid_argument{
		"InventoryWindow::PlaceItem -> trying to put item at existing item! [" + std::to_string(slot_index.first) + ", "
			+ std::to_string(slot_index.second) + "]"};
  items_slots_.at(slot_index).PutItem(std::make_unique<ItemView>(item));
}

void InventoryWindow::OnChildrenWindowEvent(Window *sender, WindowEvent event_type) {

}






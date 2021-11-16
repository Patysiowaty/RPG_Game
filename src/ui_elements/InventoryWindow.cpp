#include "InventoryWindow.hpp"
#include "../managers/InputManager.hpp"
#include "../commands/CloseWindowCommand.hpp"
#include "../managers/WindowsManager.hpp"
#include "../commands/ChangeInventoryTabCommand.hpp"
#include "../commands/ShowConcreteInventoryTabCommand.hpp"
#include <boost/range/adaptor/reversed.hpp>

InventoryWindow::InventoryWindow(PlayerController &player_controller, const std::string &wnd_name) : player_controller_{
	player_controller}, wnd_name_{wnd_name} {
  const auto kSize = static_cast<int>(ButtonType::kSize);
  for (int i = 0; i < kSize; ++i) {
	const auto kType = ButtonType(i);
	buttons_list_.emplace(kType, this);
  }
}

void InventoryWindow::OnInit() {
  Window::LoadWindowTexture("../resources/graphics/inventory.png", {0, 0, 214, 338});
  font_.loadFromFile("../resources/fonts/romulus.ttf");
  wnd_name_.SetRelativePosition({11, 11});
  wnd_name_.SetPosition(Window::GetRectangleShape().getPosition());
  wnd_name_.SetSize({192, 14});
  wnd_name_.SetAlign(TextAlign::kCenter);
  CreateSlots();
  PlaceSlots();
  SetButtons();
  SetVisible(false);
}

void InventoryWindow::Deserialize(const boost::property_tree::ptree &ptree) {
  Window::Deserialize(ptree);
}

void InventoryWindow::Update(float delta_time) {
  if (!IsActive()) return;
  Window::Update(delta_time);

  for (auto&[first, second]: items_slots_)
	second.Update(delta_time);

  for (auto&[index, button]: buttons_list_) {
	button.Update(delta_time);
  }
}

void InventoryWindow::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);

  wnd_name_.SetPosition(new_position);

  for (auto&[type, button]: buttons_list_)
	button.SetPosition(new_position);

  for (auto&[first, second]: items_slots_)
	second.SetPosition(new_position);
}

void InventoryWindow::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
  wnd_name_.Move(offset);

  for (auto&[type, button]: buttons_list_)
	button.Move(offset);

  for (auto&[first, second]: items_slots_)
	second.Move(offset);
}

void InventoryWindow::OnChildrenWindowEvent(Window *sender, WindowEvent event_type) {
  for (auto&[first, second]: items_slots_) {
	if (sender == &second) {
	  const auto kItemId = second.GetItemView()->GetItemId();
	  if (player_controller_.EquipItem(kItemId)) {
		windows_manager_->ReloadWindowsData({WindowTypes::kPlayerStatistics, WindowTypes::kInventory});
	  }
	}
  }
}

void InventoryWindow::OpenWindow() {
  Window::SetVisible(true);
  Window::Activate();
  InventoryWindow::PlaceItemsInSlots();
  ShowConcreteTab(active_tab_);
}

void InventoryWindow::CloseWindow() {
  Window::SetVisible(false);
  Window::Deactivate();
  InventoryWindow::RemoveItems();
}

void InventoryWindow::RegisterManager(WindowsManager *windows_manager) {
  windows_manager_ = windows_manager;
}

void InventoryWindow::ReloadData() {
  if (!Window::IsVisible()) return;
  InventoryWindow::RemoveItems();
  InventoryWindow::PlaceItemsInSlots();
}

void InventoryWindow::RemoveItem(const SlotIndex &slot_index) {
  items_slots_.at(slot_index).TakeOutItem();
}

void InventoryWindow::PlaceItem(const std::shared_ptr<Item> &item, const SlotIndex &slot_index) {
  if (!items_slots_.at(slot_index).IsEmpty()) {
	if (const auto &kItemView = items_slots_.at(slot_index).GetItemView(); kItemView
		&& kItemView->GetItemId() != item->GetItemId()) {
	  throw std::invalid_argument{
		  "InventoryWindow::PlaceItem -> trying to put item at existing item! [" + std::to_string(slot_index.x)
			  + ", " + std::to_string(slot_index.y) + "]"};
	} else
	  return;
  }
  items_slots_.at(slot_index).PutItem(std::make_unique<ItemView>(item));
}

void InventoryWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!IsVisible()) return;
  Window::draw(target, states);
  target.draw(wnd_name_);

  for (const auto&[type, button]: buttons_list_)
	target.draw(button, states);

  for (const auto &items_slot: boost::adaptors::reverse(items_slots_))
	target.draw(items_slot.second);
}

void InventoryWindow::CreateSlots() {
  const int kRowItemCount{5};
  const int kColumnItemCount{7};
  const auto kMaxTab = PlayerInventory::GetMaxTabs();

  for (int tab = 0; tab < kMaxTab; ++tab) {
	for (int i = 0; i < kColumnItemCount; ++i) {
	  for (int j = 0; j < kRowItemCount; ++j) {
		const SlotIndex kSlotIndex{i, j, tab};
		items_slots_.emplace(kSlotIndex, this);
		items_slots_.at(kSlotIndex).LoadWindowTexture("../resources/graphics/inventory.png", {216, 0, 36, 36});
	  }
	}
  }
}

void InventoryWindow::PlaceSlots() {
  const auto kOffset = sf::Vector2f{38, 38};
  sf::Vector2f start_pos{13, 35};

  for (auto&[first, second]: items_slots_) {
	sf::Vector2f slot_pos{static_cast<float>(first.y) * kOffset.x, static_cast<float>(first.x) * kOffset.y};
	slot_pos += start_pos;
	second.SetPosition(slot_pos);
  }
}

void InventoryWindow::PlaceItemsInSlots() {
  const int kRowItemCount{5};

  const auto &items = player_controller_.GetPlayer().GetPlayerInventory().GetInventory();
  int i{0};
  for (int j = 0; j < items.size(); ++j) {
	const auto index{j % kRowItemCount};
	if (j != 0 && index == 0) ++i;
	if (items.at(j)) {
	  SlotIndex slot_index{i, index};
	  PlaceItem(items.at(j), slot_index);
	}
  }
}

void InventoryWindow::SetButtons() {
  for (auto&[type, button]: buttons_list_) {
	switch (type) {
	  case ButtonType::kClose:
		SetCloseButton(button);
		break;
	  case ButtonType::kNextTab:
		button.LoadWindowTexture("../resources/graphics/inventory.png", {214, 38, 24, 24});
		button.SetRelativePosition({177, 301});
		button.SetPosition(Window::GetRectangleShape().getPosition());
		button.AddCommand(CommandInvoker::kLeftMouseButtonClick,
						  std::make_unique<ChangeInventoryTabCommand>(*this, DirectionCommand::kNext));
		break;
	  case ButtonType::kPreviousTab:
		button.LoadWindowTexture("../resources/graphics/inventory.png", {214, 64, 24, 24});
		button.SetRelativePosition({13, 301});
		button.SetPosition(Window::GetRectangleShape().getPosition());
		button.AddCommand(CommandInvoker::kLeftMouseButtonClick,
						  std::make_unique<ChangeInventoryTabCommand>(*this, DirectionCommand::kBack));
		break;
	  case ButtonType::kTab1:
		SetTabButton(button, 0);
		break;
	  case ButtonType::kTab2:
		SetTabButton(button, 1);
		break;
	  case ButtonType::kTab3:
		SetTabButton(button, 2);
		break;
	  case ButtonType::kTab4:
		SetTabButton(button, 3);
		break;
	  case ButtonType::kKeyTab:
		SetKeyTabButton(button);
		break;
	  default:
		break;
	}
  }
}

void InventoryWindow::SetTabButton(Button &button, int number) {
  const sf::Vector2f kTabInitPos{43, 301};
  sf::Vector2f tab_offset{26.f * number, 0};
  constexpr int kNaturalNumbersModifier{1};

  button.LoadWindowTexture("../resources/graphics/inventory.png", {214, 90, 24, 24});
  button.SetFont(font_);
  button.SetTextString(std::to_string(number + kNaturalNumbersModifier), {77, 48, 32, 255}, 20);
  button.SetRelativePosition(kTabInitPos + tab_offset);
  button.SetPosition(Window::GetRectangleShape().getPosition());
  button.AddCommand(CommandInvoker::kLeftMouseButtonClick,
					std::make_unique<ShowConcreteInventoryTabCommand>(*this, number));
}

void InventoryWindow::SetCloseButton(Button &button) {
  button.LoadWindowTexture("../resources/graphics/inventory.png", {240, 38, 10, 10});
  button.SetRelativePosition(sf::Vector2f{190.f, 13.f});
  button.AddCommand(CommandInvoker::kLeftMouseButtonClick, std::make_unique<CloseWindowCommand>(*this));
  button.SetPosition(Window::GetRectangleShape().getPosition());
}

void InventoryWindow::RemoveItems() {
  for (auto&[first, second]: items_slots_) {
	second.TakeOutItem();
  }
}

void InventoryWindow::SetKeyTabButton(Button &button) {
  const sf::Vector2f kTabPos{147, 301};

  button.LoadWindowTexture("../resources/graphics/inventory.png", {214, 117, 24, 24});
  button.SetRelativePosition(kTabPos);
  button.SetPosition(Window::GetRectangleShape().getPosition());

}

void InventoryWindow::ShowNextTab() {
  constexpr std::uint16_t kMaxTab{4};

  const auto kNextTab = active_tab_ + 1 > kMaxTab ? 0 : active_tab_ + 1;
  ShowConcreteTab(kNextTab);
}

void InventoryWindow::ShowPreviousTab() {
  constexpr std::uint16_t kMaxTab{4};
  const auto kNextTab = active_tab_ - 1 < 0 ? kMaxTab : active_tab_ - 1;
  ShowConcreteTab(kNextTab);
}

void InventoryWindow::ShowConcreteTab(std::uint16_t value) {
  active_tab_ = value;

  for (auto&[key, slot]: items_slots_) {
	if (slot.IsVisible()) {
	  slot.SetVisible(false);
	}
  }

  for (auto&[key, button]: buttons_list_) {
	if (!button.IsActive())
	  button.RestoreDefault();
  }

  for (auto&[key, slot]: items_slots_) {
	if (key.z == active_tab_) {
	  slot.SetVisible(true);
	}
  }

  switch (value) {
	case 0 :
	  buttons_list_.at(ButtonType::kTab1).Deactivate();
	  break;
	case 1:
	  buttons_list_.at(ButtonType::kTab2).Deactivate();
	  break;
	case 2:
	  buttons_list_.at(ButtonType::kTab3).Deactivate();
	  break;
	case 3:
	  buttons_list_.at(ButtonType::kTab4).Deactivate();
	  break;
	case 4:
	  buttons_list_.at(ButtonType::kKeyTab).Deactivate();
	  break;
	default:
	  break;
  }

}







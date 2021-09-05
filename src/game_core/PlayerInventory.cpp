#include "PlayerInventory.hpp"

PlayerInventory::PlayerInventory(std::uint16_t available_tabs) : available_tabs_{available_tabs} {
  available_space_ = available_tabs_ * kTabCapacity;
  remaining_slots_ = available_space_;
  inventory_.resize(available_space_);
}

bool PlayerInventory::ExpandInventory() {
  if (available_tabs_ >= kMaxTabs) return false;
  available_tabs_ += 1;
  available_space_ += kTabCapacity;
  remaining_slots_ += kTabCapacity;
  inventory_.resize(available_space_);
  return true;
}

bool PlayerInventory::RemoveItem(std::shared_ptr<Item> item) {
  if (!item) return false;
  if (!IsInInventory(item)) return false;

  const auto it = std::find(inventory_.begin(), inventory_.end(), item);
  if (it == inventory_.end())
	throw std::logic_error{"PlayerInventory::RemoveItem -> Does not find an item."};

  inventory_.erase(it);
  remaining_slots_++;
  item->SetItemLocation(ItemLocation::kNone);
  item.reset();
  return true;
}

bool PlayerInventory::PutItem(std::shared_ptr<Item> item, std::uint16_t position) {
  if (!item) return false;
  if (IsFullInventory()) return false;
  if (!IsAvailableTab(position)) return false;
  if (!IsFreeSlot(position)) return false;

  inventory_.at(position) = item;
  remaining_slots_--;
  item->SetItemLocation(ItemLocation::kCharacterInventory);
  return true;
}

bool PlayerInventory::PutItem(std::shared_ptr<Item> item) {
  if (!item) return false;
  if (IsFullInventory()) return false;

  const auto it = std::find(inventory_.begin(), inventory_.end(), nullptr);
  inventory_.insert(it, item);
  remaining_slots_--;
  item->SetItemLocation(ItemLocation::kCharacterInventory);
  return true;
}

bool PlayerInventory::SwapItems(const std::shared_ptr<Item> &lhs, const std::shared_ptr<Item> &rhs) {
  if (!lhs && !rhs) return false;
  if (!IsInInventory(lhs) && !IsInInventory(rhs)) return false;

  try {
	std::iter_swap(std::find(inventory_.begin(), inventory_.end(), lhs),
				   std::find(inventory_.begin(), inventory_.end(), rhs));
  } catch (std::exception &e) {
	return false;
  }

  return true;
}

bool PlayerInventory::ChangePosition(const std::shared_ptr<Item> &item, std::uint16_t position) {
  if (!item) return false;
  if (!IsInInventory(item)) return false;
  if (!IsAvailableTab(position)) return false;

  if (!IsFreeSlot(position)) {
	const auto &item_at_pos = inventory_.at(position);
	return SwapItems(item, item_at_pos);
  }

  inventory_.at(position) = item;
  return true;
}

bool PlayerInventory::IsFullInventory() const {
  return remaining_slots_ == 0;
}

bool PlayerInventory::IsFreeSlot(std::uint16_t position) const {
  if (!IsAvailableTab(position)) return false;
  return inventory_.at(position) == nullptr;
}

bool PlayerInventory::IsAvailableTab(std::uint16_t position) const {
  return position < available_space_;
}

bool PlayerInventory::IsInInventory(const std::shared_ptr<Item> &item) const {
  return item->GetItemLocation() == ItemLocation::kCharacterInventory;
}

void PlayerInventory::SetInventoryAvailableTabs(std::uint16_t value) {
  while (value-- && ExpandInventory());
}

std::uint16_t PlayerInventory::GetInventoryAvailableTabs() const {
  return available_tabs_;
}

std::shared_ptr<Item> PlayerInventory::GetItem(std::uint32_t item_id) const {
  const auto it = std::find_if(inventory_.cbegin(), inventory_.cend(), [=](const auto &item) {
	return item->GetItemId() == item_id;
  });

  if (!*it)
	throw std::invalid_argument{"PlayerInventory::GetItem -> no matching item with id: " + std::to_string(item_id)};

  return *it;
}

std::uint16_t PlayerInventory::GetTabCapacity() {
  return kTabCapacity;
}

std::uint16_t PlayerInventory::GetMaxTabs() {
  return kMaxTabs;
}












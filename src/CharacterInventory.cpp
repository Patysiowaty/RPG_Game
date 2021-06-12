#include "CharacterInventory.hpp"

#include <utility>
#include "Character.hpp"

CharacterInventory::CharacterInventory(std::uint16_t available_tabs) : inventory_available_tabs_{available_tabs} {
  inventory_space_ = inventory_available_tabs_ * kInventoryMaxTabs;
  remaining_slots_ = inventory_space_;
  inventory_.resize(inventory_space_);
}

CharacterInventory::~CharacterInventory() {
}

bool CharacterInventory::ExpandInventory() {
  if (inventory_available_tabs_ >= 4) return false;
  inventory_available_tabs_ += 1;
  inventory_space_ += kInventoryTabCapacity;
  remaining_slots_ += kInventoryTabCapacity;
  inventory_.resize(inventory_space_);
  return true;
}

bool CharacterInventory::RemoveItem(const std::shared_ptr<Item> &item) {
  if (!item) return false;
  if (!IsInInventory(item)) return false;

  const auto it = std::find(inventory_.begin(), inventory_.end(), item);
  if (it == inventory_.end())
	throw std::logic_error{"CharacterInventory::RemoveItem -> Does not find an item."};

  inventory_.erase(it);
  remaining_slots_++;
  item->SetItemLocation(ItemLocation::kNone);
  return true;
}

bool CharacterInventory::PutItem(const std::shared_ptr<Item> &item, std::uint16_t position) {
  if (!item) return false;
  if (IsFullInventory()) return false;
  if (!IsAvailableTab(position)) return false;
  if (!IsFreeSlot(position)) return false;

  inventory_.at(position) = item;
  item->SetItemLocation(ItemLocation::kCharacterInventory);
  remaining_slots_--;
  return true;
}

bool CharacterInventory::PutItem(const std::shared_ptr<Item> &item) {
  if (!item) return false;
  if (IsFullInventory()) return false;

  const auto it = std::find(inventory_.begin(), inventory_.end(), nullptr);
  inventory_.insert(it, item);
  remaining_slots_--;
  item->SetItemLocation(ItemLocation::kCharacterInventory);
  return true;
}

bool CharacterInventory::SwapItems(const std::shared_ptr<Item> &lhs,
								   const std::shared_ptr<Item> &rhs) {
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

bool CharacterInventory::ChangePosition(const std::shared_ptr<Item> &item, std::uint16_t position) {
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

bool CharacterInventory::IsFullInventory() const {
  return remaining_slots_ >= inventory_available_tabs_ * kInventoryTabCapacity;
}

bool CharacterInventory::IsFreeSlot(std::uint16_t position) const {
  if (!IsAvailableTab(position)) return false;
  return inventory_.at(position) == nullptr;
}

bool CharacterInventory::IsAvailableTab(std::uint16_t position) const {
  return position < inventory_space_;
}

bool CharacterInventory::IsInInventory(const std::shared_ptr<Item> &item) const {
  return item->GetCurrentLocation() == ItemLocation::kCharacterInventory;
}












#include "PlayerEquipment.hpp"

PlayerEquipment::PlayerEquipment() {
  equipment_.emplace(ItemType::kHelmet, nullptr);
  equipment_.emplace(ItemType::kRing, nullptr);
  equipment_.emplace(ItemType::kNecklace, nullptr);
  equipment_.emplace(ItemType::kGloves, nullptr);
  equipment_.emplace(ItemType::kOneHandedSword, nullptr);
  equipment_.emplace(ItemType::kArmor, nullptr);
  equipment_.emplace(ItemType::kOffHand, nullptr);
  equipment_.emplace(ItemType::kPants, nullptr);
  equipment_.emplace(ItemType::kBoots, nullptr);
}

bool PlayerEquipment::PutItem(std::shared_ptr<Item> item) {
  if (!item) return false;

  const auto item_type = item->GetItemType();
  equipment_.at(item_type) = item;
  item->SetIsEquipped(true);
  item->SetItemLocation(ItemLocation::kCharacterEquipment);

  for (auto &handler: handler_list_)
	handler->OnEquipItem(item);

  return true;
}

bool PlayerEquipment::RemoveItem(std::shared_ptr<Item> item) {
  if (!item) return false;

  if (!item->IsEquipped()) return false;

  auto item_type = item->GetItemType();
  equipment_.at(item_type) = nullptr;
  item->SetIsEquipped(false);
  item->SetItemLocation(ItemLocation::kNone);

  for (auto &handler: handler_list_)
	handler->OnTakeOffItem(item);

  return true;
}

bool PlayerEquipment::IsEmptySlot(ItemType item_type) const {
  return equipment_.at(item_type) == nullptr;
}

std::shared_ptr<Item> PlayerEquipment::GetItemAtSlot(ItemType item_type) const {
  return equipment_.at(item_type);
}

void PlayerEquipment::RegisterHandler(IItemHandler *value) {
  handler_list_.emplace_back(value);
}



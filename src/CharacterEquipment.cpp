#include "CharacterEquipment.hpp"

CharacterEquipment::CharacterEquipment() {
  equipment_.emplace(ItemType::kHelmet, nullptr);
  equipment_.emplace(ItemType::kRing, nullptr);
  equipment_.emplace(ItemType::kNecklace, nullptr);
  equipment_.emplace(ItemType::kGloves, nullptr);
  equipment_.emplace(ItemType::kWeapon, nullptr);
  equipment_.emplace(ItemType::kArmor, nullptr);
  equipment_.emplace(ItemType::kOffHand, nullptr);
  equipment_.emplace(ItemType::kPants, nullptr);
  equipment_.emplace(ItemType::kBoots, nullptr);
}

bool CharacterEquipment::PutItem(const std::shared_ptr<Item> &item) {
  if (!item) return false;

  const auto item_type = item->GetItemType();
  equipment_.at(item_type) = item;
  item->SetIsEquipped(true);
  item->ChangeItemLocation(ItemLocation::kCharacterEquipment);
  return true;
}

bool CharacterEquipment::RemoveItem(const std::shared_ptr<Item> &item) {
  if (!item) return false;

  if (!item->IsEquipped()) return false;

  auto item_type = item->GetItemType();
  equipment_.at(item_type) = nullptr;
  item->SetIsEquipped(false);
  item->ChangeItemLocation(ItemLocation::kNone);
  return true;
}

bool CharacterEquipment::IsEmptySlot(ItemType item_type) const {
  return equipment_.at(item_type) == nullptr;
}

const std::shared_ptr<Item>& CharacterEquipment::GetItemAtSlot(ItemType item_type) const {
  return equipment_.at(item_type);
}



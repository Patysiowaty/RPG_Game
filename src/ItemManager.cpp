#include "ItemManager.hpp"

ItemManager::ItemManager(CharacterInventory *inventory, CharacterEquipment *equipment, CharacterLevel *level,
						 std::uint32_t *id)
	: inventory_{inventory}, equipment_{equipment}, level_{level}, id_{id} {}

ItemManagerEC ItemManager::EquipItem(const std::shared_ptr<Item> &item) {
  if (!item) return ItemManagerEC::kItemDoesNotExist;
  if (item->GetOwnerId() != *id_) return ItemManagerEC::kItemDoesNotBelongToCharacter;
  if (!inventory_->IsInInventory(item)) return ItemManagerEC::kItemIsNotInInventory;
  if (level_->GetLevel() < item->GetLevelRequirement()) return ItemManagerEC::kLevelIsTooLow;

  try {
	if (!inventory_->RemoveItem(item)) return ItemManagerEC::kFailedRemovingItem;
	if (auto occupied_slot = item->GetItemType(); !equipment_->IsEmptySlot(occupied_slot)) {
	  const auto &item_at_slot = equipment_->GetItemAtSlot(occupied_slot);
	  if (const auto err_code = Swap(item, item_at_slot); err_code != ItemManagerEC::kNone) return err_code;
	} else {
	  if (!equipment_->PutItem(item)) {
		inventory_->PutItem(item);
		return ItemManagerEC::kFailedInsertItem;
	  }
	}
  } catch (std::logic_error &e) {
	//TODO: Log this!
	return ItemManagerEC::kItemIsNotInInventory;
  }

  for (const auto handler : handlers_) {
	handler->OnEquipItem(item);
  }

  return ItemManagerEC::kNone;
}

ItemManagerEC ItemManager::TakeOffItem(const std::shared_ptr<Item> &item) {
  if (!item) return ItemManagerEC::kItemDoesNotExist;
  if (item->GetOwnerId() != *id_) return ItemManagerEC::kItemDoesNotBelongToCharacter;
  if (!item->IsEquipped() && equipment_->GetItemAtSlot(item->GetItemType()) != item)
	return ItemManagerEC::kItemIsNotEquipped;
  if (inventory_->IsFullInventory()) return ItemManagerEC::kInventoryIsFull;
  try {
	if (!equipment_->RemoveItem(item)) return ItemManagerEC::kFailedTakingOffItem;
  } catch (std::logic_error &e) {
	//TODO: Log this!
	return ItemManagerEC::kItemIsNotInInventory;
  }
  if (!inventory_->PutItem(item)) {
	equipment_->PutItem(item);
	return ItemManagerEC::kFailedInsertItem;
  }

  for (const auto handler : handlers_) {
	handler->OnTakeOffItem(item);
  }

  return ItemManagerEC::kNone;
}

ItemManagerEC ItemManager::UseItem(const std::shared_ptr<Item> &item) {
  if (!item) return ItemManagerEC::kItemDoesNotExist;
  if (item->GetOwnerId() != *id_) return ItemManagerEC::kItemDoesNotBelongToCharacter;
  if (!inventory_->IsInInventory(item)) return ItemManagerEC::kItemIsNotInInventory;
  if (level_->GetLevel() < item->GetLevelRequirement()) return ItemManagerEC::kLevelIsTooLow;
  if (!inventory_->RemoveItem(item)) return ItemManagerEC::kFailedRemovingItem;

  for (const auto handler : handlers_) {
	handler->OnUsedItem(item);
  }
  return ItemManagerEC::kNone;
}

ItemManagerEC ItemManager::Swap(const std::shared_ptr<Item> &inventory_item,
								const std::shared_ptr<Item> &equipment_item) {
  if (equipment_item->GetOwnerId() != *id_) return ItemManagerEC::kItemDoesNotBelongToCharacter;
  if (!equipment_->RemoveItem(equipment_item)) return ItemManagerEC::kItemIsNotEquipped;
  if (inventory_->IsFullInventory() && !inventory_->PutItem(equipment_item)) return ItemManagerEC::kInventoryIsFull;
  if (!equipment_->IsEmptySlot(equipment_item->GetItemType())) return ItemManagerEC::kFailedTakingOffItem;
  if (!equipment_->PutItem(inventory_item)) return ItemManagerEC::kItemDoesNotExist;
  return ItemManagerEC::kNone;
}

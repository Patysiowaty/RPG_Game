#include "ItemsInteractor.hpp"

ItemsInteractor::ItemsInteractor(PlayerInventory *inventory, PlayerEquipment *equipment, PlayerLevel *level,
								 std::uint32_t *id)
	: inventory_{inventory}, equipment_{equipment}, level_{level}, id_{id} {}

ItemInteractorErrorCode ItemsInteractor::EquipItem(const std::shared_ptr<Item> &item) {
  if (!item) return ItemInteractorErrorCode::kItemDoesNotExist;
  if (item->GetOwnerId() != *id_) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (!inventory_->IsInInventory(item)) return ItemInteractorErrorCode::kItemIsNotInInventory;
  if (level_->GetLevel() < item->GetLevelRequirement()) return ItemInteractorErrorCode::kLevelIsTooLow;

  try {
	if (!inventory_->RemoveItem(item)) return ItemInteractorErrorCode::kFailedRemovingItem;
	if (auto occupied_slot = item->GetItemType(); !equipment_->IsEmptySlot(occupied_slot)) {
	  const auto &item_at_slot = equipment_->GetItemAtSlot(occupied_slot);
	  if (const auto err_code = Swap(item, item_at_slot); err_code != ItemInteractorErrorCode::kNone) return err_code;
	} else {
	  if (!equipment_->PutItem(item)) {
		inventory_->PutItem(item);
		return ItemInteractorErrorCode::kFailedInsertItem;
	  }
	}
  } catch (std::logic_error &e) {
	return ItemInteractorErrorCode::kItemIsNotInInventory;
  }

  for (const auto handler : handlers_) {
	handler->OnEquipItem(item);
  }

  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::TakeOffItem(const std::shared_ptr<Item> &item) {
  if (!item) return ItemInteractorErrorCode::kItemDoesNotExist;
  if (item->GetOwnerId() != *id_) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (!item->IsEquipped() && equipment_->GetItemAtSlot(item->GetItemType()) != item)
	return ItemInteractorErrorCode::kItemIsNotEquipped;
  if (inventory_->IsFullInventory()) return ItemInteractorErrorCode::kInventoryIsFull;
  try {
	if (!equipment_->RemoveItem(item)) return ItemInteractorErrorCode::kFailedTakingOffItem;
  } catch (std::logic_error &e) {
	return ItemInteractorErrorCode::kItemIsNotInInventory;
  }
  if (!inventory_->PutItem(item)) {
	equipment_->PutItem(item);
	return ItemInteractorErrorCode::kFailedInsertItem;
  }

  for (const auto handler : handlers_) {
	handler->OnTakeOffItem(item);
  }

  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::UseItem(const std::shared_ptr<Item> &item) {
  if (!item) return ItemInteractorErrorCode::kItemDoesNotExist;
  if (item->GetOwnerId() != *id_) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (!inventory_->IsInInventory(item)) return ItemInteractorErrorCode::kItemIsNotInInventory;
  if (level_->GetLevel() < item->GetLevelRequirement()) return ItemInteractorErrorCode::kLevelIsTooLow;
  if (!inventory_->RemoveItem(item)) return ItemInteractorErrorCode::kFailedRemovingItem;

  for (const auto handler : handlers_) {
	handler->OnUsedItem(item);
  }
  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::Swap(const std::shared_ptr<Item> &inventory_item,
											  const std::shared_ptr<Item> &equipment_item) {
  if (equipment_item->GetOwnerId() != *id_) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (!equipment_->RemoveItem(equipment_item)) return ItemInteractorErrorCode::kItemIsNotEquipped;
  if (inventory_->IsFullInventory() && !inventory_->PutItem(equipment_item))
	return ItemInteractorErrorCode::kInventoryIsFull;
  if (!equipment_->IsEmptySlot(equipment_item->GetItemType())) return ItemInteractorErrorCode::kFailedTakingOffItem;
  if (!equipment_->PutItem(inventory_item)) return ItemInteractorErrorCode::kItemDoesNotExist;
  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::AddItem(std::shared_ptr<Item> item) {
  if (inventory_->IsFullInventory()) return ItemInteractorErrorCode::kInventoryIsFull;
  if (!inventory_->PutItem(item)) return ItemInteractorErrorCode::kFailedInsertItem;
  item->SetOwnerId(*id_);
  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::DeleteItem(std::shared_ptr<Item> item) {
  if (item->GetOwnerId() != *id_) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (item->IsEquipped()) {
	if (!equipment_->RemoveItem(item)) return ItemInteractorErrorCode::kFailedTakingOffItem;
	return ItemInteractorErrorCode::kNone;
  }
  if (!inventory_->IsInInventory(item)) return ItemInteractorErrorCode::kItemIsNotInInventory;
  if (!inventory_->RemoveItem(item)) return ItemInteractorErrorCode::kFailedRemovingItem;

  return ItemInteractorErrorCode::kNone;
}

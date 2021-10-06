#include "ItemsInteractor.hpp"

ItemsInteractor::ItemsInteractor(Player &player)
	: player_{player} {}

ItemInteractorErrorCode ItemsInteractor::EquipItem(std::shared_ptr<Item> item) {
  auto &inventory = player_.GetPlayerInventory();
  auto &equipment = player_.GetPlayerEquipment();
  const auto kPlayerLevel = player_.GetPlayerLevel().GetLevel();
  const auto kPlayerId = player_.GetId();

  if (!item) return ItemInteractorErrorCode::kItemDoesNotExist;
  if (item->GetOwnerId() != kPlayerId) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (!inventory.IsInInventory(item)) return ItemInteractorErrorCode::kItemIsNotInInventory;
  if (kPlayerLevel < item->GetLevelRequirement()) return ItemInteractorErrorCode::kLevelIsTooLow;

  try {
	if (auto occupied_slot = item->GetItemType(); !equipment.IsEmptySlot(occupied_slot)) {
	  auto item_at_slot = equipment.GetItemAtSlot(occupied_slot);
	  return Swap(item, item_at_slot);
	} else {
	  if (!inventory.RemoveItem(item)) return ItemInteractorErrorCode::kFailedRemovingItem;
	  if (!equipment.PutItem(item)) {
		inventory.PutItem(item);
		return ItemInteractorErrorCode::kFailedInsertItem;
	  }
	}
  } catch (std::logic_error &e) {
	return ItemInteractorErrorCode::kItemIsNotInInventory;
  }

  for (const auto handler: handlers_) {
	handler->OnEquipItem(item);
  }

  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::TakeOffItem(std::shared_ptr<Item> item) {
  auto &inventory = player_.GetPlayerInventory();
  auto &equipment = player_.GetPlayerEquipment();
  const auto kPlayerId = player_.GetId();

  if (!item) return ItemInteractorErrorCode::kItemDoesNotExist;

  if (item->GetOwnerId() != kPlayerId) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (!item->IsEquipped() && equipment.GetItemAtSlot(item->GetItemType()) != item)
	return ItemInteractorErrorCode::kItemIsNotEquipped;
  if (inventory.IsFullInventory()) return ItemInteractorErrorCode::kInventoryIsFull;
  try {
	if (!equipment.RemoveItem(item)) return ItemInteractorErrorCode::kFailedTakingOffItem;
  } catch (std::logic_error &e) {
	return ItemInteractorErrorCode::kItemIsNotInInventory;
  }
  if (!inventory.PutItem(item)) {
	equipment.PutItem(item);
	return ItemInteractorErrorCode::kFailedInsertItem;
  }

  for (const auto handler: handlers_) {
	handler->OnTakeOffItem(item);
  }

  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::UseItem(const std::shared_ptr<Item> &item) {
  auto &inventory = player_.GetPlayerInventory();
  const auto kPlayerLevel = player_.GetPlayerLevel().GetLevel();
  const auto kPlayerId = player_.GetId();

  if (!item) return ItemInteractorErrorCode::kItemDoesNotExist;
  if (item->GetOwnerId() != kPlayerId) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (!inventory.IsInInventory(item)) return ItemInteractorErrorCode::kItemIsNotInInventory;
  if (kPlayerLevel < item->GetLevelRequirement()) return ItemInteractorErrorCode::kLevelIsTooLow;
  if (item->GetItemType() != ItemType::kConsumptive) return ItemInteractorErrorCode::kWrongItemType;

  if (!inventory.RemoveItem(item)) return ItemInteractorErrorCode::kFailedRemovingItem;

  for (const auto handler: handlers_) {
	handler->OnUsedItem(std::dynamic_pointer_cast<IConsumable>(item));
  }
  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::Swap(const std::shared_ptr<Item> &inventory_item,
											  const std::shared_ptr<Item> &equipment_item) {
  if (auto ec = TakeOffItem(equipment_item); ec != ItemInteractorErrorCode::kNone)
	return ec;
  if (auto ec = EquipItem(inventory_item); ec != ItemInteractorErrorCode::kNone)
	return ec;

  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::AddItem(std::shared_ptr<Item> item) {
  auto &inventory = player_.GetPlayerInventory();
  const auto kPlayerId = player_.GetId();

  if (inventory.IsFullInventory()) return ItemInteractorErrorCode::kInventoryIsFull;
  if (!inventory.PutItem(item)) return ItemInteractorErrorCode::kFailedInsertItem;
  item->SetOwnerId(kPlayerId);
  return ItemInteractorErrorCode::kNone;
}

ItemInteractorErrorCode ItemsInteractor::DeleteItem(std::shared_ptr<Item> item) {
  auto &inventory = player_.GetPlayerInventory();
  auto &equipment = player_.GetPlayerEquipment();
  const auto kPlayerId = player_.GetId();

  if (item->GetOwnerId() != kPlayerId) return ItemInteractorErrorCode::kItemDoesNotBelongToCharacter;
  if (item->IsEquipped()) {
	if (!equipment.RemoveItem(item)) return ItemInteractorErrorCode::kFailedTakingOffItem;
	return ItemInteractorErrorCode::kNone;
  }
  if (!inventory.IsInInventory(item)) return ItemInteractorErrorCode::kItemIsNotInInventory;
  if (!inventory.RemoveItem(item)) return ItemInteractorErrorCode::kFailedRemovingItem;

  return ItemInteractorErrorCode::kNone;
}

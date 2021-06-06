#ifndef ITEMMANAGEREC_HPP
#define ITEMMANAGEREC_HPP

enum class ItemManagerEC {
  kNone = 0,
  kItemDoesNotExist,
  kItemDoesNotBelongToCharacter,
  kInventoryIsFull,
  kInventorySlotIsOccupied,
  kItemIsNotInInventory,
  kInventorySlotIsUnavailable,
  kItemIsNotEquipped,
  kFailedTakingOffItem,
  kFailedInsertItem,
  kFailedRemovingItem,
  kLevelIsTooLow
};

#endif //ITEMMANAGEREC_HPP

#ifndef ITEMINTERACTORERRORCODE_HPP
#define ITEMINTERACTORERRORCODE_HPP

enum class ItemInteractorErrorCode {
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

#endif //ITEMINTERACTORERRORCODE_HPP

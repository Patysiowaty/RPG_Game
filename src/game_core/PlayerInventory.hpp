#ifndef PLAYERINVENTORY_HPP
#define PLAYERINVENTORY_HPP

#include <memory>
#include <vector>
#include "../item_types/Item.hpp"
#include "../enums/ErrorCodes/ItemInteractorErrorCode.hpp"
#include "../interfaces/IItemList.hpp"

class PlayerInventory : IItemList {
 public:
  explicit PlayerInventory(std::uint16_t available_tabs = 1);
  ~PlayerInventory();

  void SetInventoryAvailableTabs(std::uint16_t value);

  bool ExpandInventory();
  bool RemoveItem(std::shared_ptr<Item> item) override;
  bool PutItem(std::shared_ptr<Item> item, uint16_t position);
  bool PutItem(std::shared_ptr<Item> item) override;

  std::shared_ptr<Item> GetItem(std::uint32_t item_id) const;

  bool ChangePosition(const std::shared_ptr<Item> &item, std::uint16_t position);
  bool SwapItems(const std::shared_ptr<Item> &lhs, const std::shared_ptr<Item> &rhs);
  bool IsFullInventory() const;
  bool IsInInventory(const std::shared_ptr<Item> &item) const;
  bool IsFreeSlot(std::uint16_t position) const;
  bool IsAvailableTab(std::uint16_t position) const;

  std::uint16_t GetInventoryAvailableTabs() const;

 private:
  static constexpr std::uint16_t kInventoryTabCapacity = 20;
  static constexpr std::uint16_t kInventoryMaxTabs = 4;
  std::uint16_t inventory_available_tabs_ = 1;
  std::uint16_t inventory_space_;
  std::uint16_t remaining_slots_;

  std::vector<std::shared_ptr<Item>> inventory_;
};

#endif //PLAYERINVENTORY_HPP

#ifndef CHARACTERINVENTORY_HPP
#define CHARACTERINVENTORY_HPP

#include <memory>
#include <vector>
#include "item_types/Item.hpp"
#include "enums/ErrorCodes/ItemManagerEC.hpp"
#include "Interfaces/IItemList.hpp"

class CharacterInventory : IItemList {
 public:
  explicit CharacterInventory(std::uint16_t available_tabs = 1);
  ~CharacterInventory();

  bool ExpandInventory();
  bool RemoveItem(const std::shared_ptr<Item> &item) override;
  bool PutItem(const std::shared_ptr<Item> &item, uint16_t position);
  bool PutItem(const std::shared_ptr<Item> &item) override;
  bool ChangePosition(const std::shared_ptr<Item> &item, std::uint16_t position);
  bool SwapItems(const std::shared_ptr<Item> &lhs, const std::shared_ptr<Item> &rhs);
  bool IsFullInventory() const;
  bool IsInInventory(const std::shared_ptr<Item> &item) const;
  bool IsFreeSlot(std::uint16_t position) const;
  bool IsAvailableTab(std::uint16_t position) const;

 private:
  static constexpr std::uint16_t kInventoryTabCapacity = 20;
  static constexpr std::uint16_t kInventoryMaxTabs = 4;
  std::uint16_t inventory_available_tabs_ = 1;
  std::uint16_t inventory_space_;
  std::uint16_t remaining_slots_;

  std::vector<std::shared_ptr<Item>> inventory_;
};

#endif //CHARACTERINVENTORY_HPP

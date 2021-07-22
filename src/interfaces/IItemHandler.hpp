#ifndef IITEMHANDLER_HPP
#define IITEMHANDLER_HPP
#include "../item_types/Item.hpp"
#include "IConsumable.hpp"
#include <memory>

class IItemHandler {
 public:
  virtual ~IItemHandler() = default;
  virtual void OnEquipItem(const std::shared_ptr<Item> &item) = 0;
  virtual void OnTakeOffItem(const std::shared_ptr<Item> &item) = 0;
  virtual void OnUsedItem(const std::shared_ptr<IConsumable> &item) = 0;
};

#endif //IITEMHANDLER_HPP

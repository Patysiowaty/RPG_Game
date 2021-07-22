#ifndef IITEMLIST_HPP
#define IITEMLIST_HPP

#include <memory>
#include "../item_types/Item.hpp"

class IItemList {
 public:
  virtual ~IItemList() = default;
  virtual bool PutItem(std::shared_ptr<Item> item) = 0;
  virtual bool RemoveItem(std::shared_ptr<Item> item) = 0;
};

#endif //IITEMLIST_HPP

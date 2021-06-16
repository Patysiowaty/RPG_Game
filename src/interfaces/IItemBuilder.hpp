#ifndef IITEMBUILDER_HPP
#define IITEMBUILDER_HPP

#include <string>
#include <memory>
#include "../item_types/Item.hpp"

class IItemBuilder {
 public:
  virtual std::shared_ptr<Item> MakeItem() = 0;
  virtual bool BuildRawItem() = 0;
  virtual bool BuildAttributes() = 0;
  virtual bool BuildStatistics() = 0;
};

#endif //IITEMBUILDER_HPP

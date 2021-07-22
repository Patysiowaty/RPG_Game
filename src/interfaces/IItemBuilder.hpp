#ifndef IITEMBUILDER_HPP
#define IITEMBUILDER_HPP

#include <string>
#include <memory>
#include "../item_types/Item.hpp"

class IItemBuilder {
 public:
  virtual ~IItemBuilder() = default;
  virtual std::shared_ptr<Item> MakeItem(std::uint32_t template_id) = 0;
  virtual bool BuildRawItem() = 0;
  virtual bool BuildAttributes() = 0;
  virtual bool BuildStatistics() = 0;
};

#endif //IITEMBUILDER_HPP

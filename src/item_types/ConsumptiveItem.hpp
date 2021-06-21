#ifndef CONSUMPTIVEITEM_HPP
#define CONSUMPTIVEITEM_HPP
#include "Item.hpp"
#include "../interfaces/IConsumable.hpp"
#include <memory>

class ConsumptiveItem : public Item, public IConsumable {
 public:
  ConsumptiveItem();
  explicit ConsumptiveItem(std::uint32_t item_id);

  ConsumptionEffect GetAfterConsumptionEffect() override;
};

#endif //CONSUMPTIVEITEM_HPP

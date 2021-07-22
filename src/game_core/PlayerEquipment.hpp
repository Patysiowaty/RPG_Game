#ifndef PLAYEREQUIPMENT_HPP
#define PLAYEREQUIPMENT_HPP

#include <memory>
#include <map>
#include "../item_types/Item.hpp"
#include "../enums/ItemType.hpp"
#include "../interfaces/IItemList.hpp"

class PlayerEquipment : public IItemList {
 public:
  PlayerEquipment();

  bool PutItem(std::shared_ptr<Item> item) override;
  bool RemoveItem(std::shared_ptr<Item> item) override;
  bool IsEmptySlot(ItemType item_type) const;
  std::shared_ptr<Item> GetItemAtSlot(ItemType item_type) const;

 private:
  using Equipment = std::map<ItemType, std::shared_ptr<Item>>;
  Equipment equipment_;
};

#endif //PLAYEREQUIPMENT_HPP

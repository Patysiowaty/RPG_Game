#ifndef CHARACTEREQUIPMENT_HPP
#define CHARACTEREQUIPMENT_HPP

#include <memory>
#include <map>
#include "item_types/Item.hpp"
#include "enums/ItemType.hpp"
#include "interfaces/IItemList.hpp"

class CharacterEquipment : public IItemList {
 public:
  CharacterEquipment();

  bool PutItem(std::shared_ptr<Item> item) override;
  bool RemoveItem(std::shared_ptr<Item> item) override;
  bool IsEmptySlot(ItemType item_type) const;
  std::shared_ptr<Item> GetItemAtSlot(ItemType item_type) const;

 private:
  std::map<ItemType, std::shared_ptr<Item>> equipment_;
};

#endif //CHARACTEREQUIPMENT_HPP

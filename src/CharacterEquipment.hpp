#ifndef CHARACTEREQUIPMENT_HPP
#define CHARACTEREQUIPMENT_HPP

#include <memory>
#include <map>
#include "item_types/Item.hpp"
#include "enums/ItemType.hpp"
#include "Interfaces/IItemList.hpp"

class CharacterEquipment : public IItemList {
 public:
  CharacterEquipment();

  bool PutItem(const std::shared_ptr<Item> &item) override;
  bool RemoveItem(const std::shared_ptr<Item> &item) override;
  bool IsEmptySlot(ItemType item_type) const;
  const std::shared_ptr<Item> &GetItemAtSlot(ItemType item_type) const;

 private:
  std::map<ItemType, std::shared_ptr<Item>> equipment_;
};

#endif //CHARACTEREQUIPMENT_HPP

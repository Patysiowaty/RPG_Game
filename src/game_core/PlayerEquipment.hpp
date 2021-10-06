#ifndef PLAYEREQUIPMENT_HPP
#define PLAYEREQUIPMENT_HPP

#include <memory>
#include <map>
#include <vector>
#include "../item_types/Item.hpp"
#include "../enums/ItemType.hpp"
#include "../interfaces/IItemList.hpp"
#include "../interfaces/IItemHandler.hpp"
#include "../interfaces/IPublisher.hpp"

class PlayerEquipment : public IItemList, public IPublisher<IItemHandler> {
 public:
  PlayerEquipment();

  bool PutItem(std::shared_ptr<Item> item) override;
  bool RemoveItem(std::shared_ptr<Item> item) override;
  bool IsEmptySlot(ItemType item_type) const;
  void RegisterHandler(IItemHandler *value) override;
  const std::shared_ptr<Item> &GetItemAtSlot(ItemType item_type) const;

 private:
  std::vector<IItemHandler *> handler_list_;
  using Equipment = std::map<ItemType, std::shared_ptr<Item>>;
  Equipment equipment_;
};

#endif //PLAYEREQUIPMENT_HPP

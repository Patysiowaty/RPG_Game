#ifndef ITEMMANAGER_HPP
#define ITEMMANAGER_HPP
#include "CharacterInventory.hpp"
#include "CharacterEquipment.hpp"
#include "enums/ErrorCodes/ItemManagerEC.hpp"
#include "CharacterLevel.hpp"
#include "interfaces/IItemHandler.hpp"

class ItemManager {
 public:
  ItemManager(CharacterInventory *inventory, CharacterEquipment *equipment, CharacterLevel *level, std::uint32_t id);
  ItemManagerEC EquipItem(const std::shared_ptr<Item> &item);
  ItemManagerEC TakeOffItem(const std::shared_ptr<Item> &item);
  ItemManagerEC UseItem(const std::shared_ptr<Item> &item);

  void RegisterHandler(IItemHandler *handler) { handlers_.push_back(handler); }

 private:
  ItemManagerEC Swap(const std::shared_ptr<Item> &inventory_item, const std::shared_ptr<Item> &equipment_item);

 private:
  CharacterInventory *inventory_;
  CharacterEquipment *equipment_;
  CharacterLevel *level_;
  std::uint32_t id_;
  std::vector<IItemHandler *> handlers_;
};
#endif //ITEMMANAGER_HPP

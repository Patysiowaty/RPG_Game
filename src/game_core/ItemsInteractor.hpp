#ifndef ITEMSINTERACTOR_HPP
#define ITEMSINTERACTOR_HPP
#include "PlayerInventory.hpp"
#include "PlayerEquipment.hpp"
#include "../enums/ErrorCodes/ItemInteractorErrorCode.hpp"
#include "PlayerLevel.hpp"
#include "../interfaces/IItemHandler.hpp"

class ItemsInteractor : public IPublisher<IItemHandler> {
 public:
  ItemsInteractor(PlayerInventory &inventory, PlayerEquipment &equipment, PlayerLevel &level, std::uint32_t &id);
  ItemInteractorErrorCode EquipItem(const std::shared_ptr<Item> &item);
  ItemInteractorErrorCode TakeOffItem(const std::shared_ptr<Item> &item);
  ItemInteractorErrorCode UseItem(const std::shared_ptr<Item> &item);
  ItemInteractorErrorCode AddItem(std::shared_ptr<Item> item);
  ItemInteractorErrorCode DeleteItem(std::shared_ptr<Item> item);

  void RegisterHandler(IItemHandler *handler) override { handlers_.push_back(handler); }

 private:
  ItemInteractorErrorCode Swap(const std::shared_ptr<Item> &inventory_item,
							   const std::shared_ptr<Item> &equipment_item);

 private:
  PlayerInventory &inventory_;
  PlayerEquipment &equipment_;
  PlayerLevel &level_;
  std::uint32_t &id_;
  std::vector<IItemHandler *> handlers_;
};
#endif //ITEMSINTERACTOR_HPP

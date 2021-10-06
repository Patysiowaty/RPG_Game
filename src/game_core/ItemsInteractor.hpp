#ifndef ITEMSINTERACTOR_HPP
#define ITEMSINTERACTOR_HPP
#include "../enums/ErrorCodes/ItemInteractorErrorCode.hpp"
#include "../interfaces/IItemHandler.hpp"
#include "../models/Player.hpp"

class ItemsInteractor : public IPublisher<IItemHandler> {
 public:
  ItemsInteractor(Player &player);
  ItemInteractorErrorCode EquipItem(std::shared_ptr<Item> item);
  ItemInteractorErrorCode TakeOffItem(std::shared_ptr<Item> item);
  ItemInteractorErrorCode UseItem(const std::shared_ptr<Item> &item);
  ItemInteractorErrorCode AddItem(std::shared_ptr<Item> item);
  ItemInteractorErrorCode DeleteItem(std::shared_ptr<Item> item);

  void RegisterHandler(IItemHandler *handler) override { handlers_.push_back(handler); }

 private:
  ItemInteractorErrorCode Swap(const std::shared_ptr<Item> &inventory_item,
							   const std::shared_ptr<Item> &equipment_item);

 private:
  Player &player_;
  std::vector<IItemHandler *> handlers_;
};
#endif //ITEMSINTERACTOR_HPP

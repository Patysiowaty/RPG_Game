#ifndef CHARACTERDATAUPDATER_HPP
#define CHARACTERDATAUPDATER_HPP
#include "IItemHandler.hpp"
#include "CharacterStatistics.hpp"
#include "CharacterAttributes.hpp"
#include "item_types/Item.hpp"
#include <memory>

class CharacterDataUpdater : public IItemHandler {
 public:
  CharacterDataUpdater(CharacterStatistics *statistics, CharacterAttributes *attributes);
  void OnEquipItem(const std::shared_ptr<Item> &item) override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override;
  void OnUsedItem(const std::shared_ptr<Item> &item) override;

 private:
  CharacterStatistics *statistics_;
  CharacterAttributes *attributes_;
};
#endif //CHARACTERDATAUPDATER_HPP

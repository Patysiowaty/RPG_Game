#ifndef CHARACTERDATAUPDATER_HPP
#define CHARACTERDATAUPDATER_HPP
#include "interfaces/IItemHandler.hpp"
#include "CharacterStatistics.hpp"
#include "CharacterAttributes.hpp"
#include "item_types/Item.hpp"
#include <memory>

class CharacterDataUpdater : public IItemHandler, public ILevelHandler {
 public:
  CharacterDataUpdater(CharacterStatistics *statistics, CharacterAttributes *attributes);
  void OnEquipItem(const std::shared_ptr<Item> &item) override;
  void OnLevelRaise() override;
  void OnLevelDowngrade() override;
  void OnLevelUpdate(int value) override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override;
  void OnUsedItem(const std::shared_ptr<Item> &item) override;

 private:
  CharacterStatistics *statistics_;
  CharacterAttributes *attributes_;
};
#endif //CHARACTERDATAUPDATER_HPP

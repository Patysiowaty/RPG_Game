#ifndef CHARACTERDATAMANAGER_HPP
#define CHARACTERDATAMANAGER_HPP
#include "interfaces/IItemHandler.hpp"
#include "CharacterStatistics.hpp"
#include "CharacterAttributes.hpp"
#include "CharacterLevel.hpp"
#include "item_types/Item.hpp"
#include "interfaces/IAttributesHandler.hpp"
#include <memory>

class CharacterDataManager : public IItemHandler, public ILevelHandler, public IAttributesHandler {
 public:
  CharacterDataManager(CharacterStatistics *statistics, CharacterAttributes *attributes, CharacterLevel *level);
  void OnEquipItem(const std::shared_ptr<Item> &item) override;
  void OnLevelRaise() override;
  void OnLevelDowngrade() override;
  void OnLevelUpdate(int value) override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override;
  void OnUsedItem(const std::shared_ptr<Item> &item) override;
  void OnAttributesRaise() override;
  void OnAttributesLower() override;
  void OnAttributeRaise(AttributeType attribute_type) override;
  void OnAttributeLower(AttributeType attribute_type) override;

 private:
  CharacterStatistics *statistics_;
  CharacterAttributes *attributes_;
  CharacterLevel *level_;
};
#endif //CHARACTERDATAMANAGER_HPP

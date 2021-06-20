#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Character.hpp"
#include "item_types/SwordItem.hpp"
#include "item_types/ConsumptiveItem.hpp"
#include "interfaces/IjsonSerializable.hpp"

class Player : public Character, public IJSONSerializable {
 public:
  Player();

  void Attack() override;
  void MoveCharacter() override;

  boost::property_tree::ptree Serialize() override;
  void Deserialize(const boost::property_tree::ptree &ptree) override;

  ItemsInteractor &GetItemsInteractor() { return items_interactor_; }
  PlayerLevel &GetLevel() { return player_level_; }

 private:
  PlayerAttributes player_attributes_;
  PlayerStatistics player_statistics_;
  PlayerEquipment player_equipment_;
  PlayerInventory player_inventory_;
  PlayerLevel player_level_;
  ItemsInteractor items_interactor_;
};

#endif //PLAYER_HPP

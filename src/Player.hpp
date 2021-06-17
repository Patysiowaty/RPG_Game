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

 private:
};

#endif //PLAYER_HPP

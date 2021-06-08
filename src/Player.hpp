#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Character.hpp"
#include "item_types/SwordItem.hpp"
#include "item_types/ConsumptiveItem.hpp"

class Player : public Character {
 public:
  Player(std::uint32_t id, std::string character_name);

  void Attack() override;
  void MoveCharacter() override;
  void OnBattleEnd(bool winner) override;

 private:
};

#endif //PLAYER_HPP

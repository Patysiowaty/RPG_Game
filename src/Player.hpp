#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Character.hpp"
#include "PlayerExperience.hpp"
#include "item_types/SwordItem.hpp"
#include "item_types/ConsumptiveItem.hpp"

class Player : public Character {
 public:
  Player();

  void OnAttributesUpdate() override;
  void OnStatisticsUpdate() override;

  void Attack() override;
  void MoveCharacter() override;
  void OnBattleEnd(bool winner) override;

 private:
  PlayerExperience player_experience_;
};

#endif //PLAYER_HPP

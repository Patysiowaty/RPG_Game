#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "../interfaces/IFightable.hpp"
#include "../enums/FIghterTurn.hpp"
#include "../enums/BattleWinner.hpp"

class Battle {
 public:
  Battle(IFightable &attacker, IFightable &defender);

  bool IsCompleted() const { return completed_; }

  void NextTurn();
  void InitializeBattle();

 private:
  void EndFight(BattleWinner winner);
  void DistributeRewardsAfterFight(IFightable &winner, IFightable &looser);
  void AttackerTurn();
  void DefenderTurn();
  BattleWinner GetWinner();

 private:
  IFightable &attacker_;
  IFightable &defender_;
  FighterTurn fighter_turn_{FighterTurn::kAttacker};
  bool completed_{false};
};

#endif //BATTLE_HPP

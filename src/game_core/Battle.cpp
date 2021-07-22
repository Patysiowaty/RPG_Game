#include <stdexcept>
#include "Battle.hpp"
#include "../enums/FIghterTurn.hpp"
#include "../enums/BattleWinner.hpp"

Battle::Battle(IFightable &attacker, IFightable &defender) : attacker_{attacker}, defender_{defender} {
}

void Battle::InitializeBattle() {
  attacker_.SetBattleState(BattleStates::kInBattle);
  defender_.SetBattleState(BattleStates::kInBattle);
}

void Battle::NextTurn() {

  switch (fighter_turn_) {
	case FighterTurn::kAttacker:
	  AttackerTurn();
	  fighter_turn_ = FighterTurn::kDefender;
	  break;
	case FighterTurn::kDefender:
	  DefenderTurn();
	  fighter_turn_ = FighterTurn::kAttacker;
	  break;
  }

  if (const auto winner = GetWinner(); winner != BattleWinner::kNone) {
	EndFight(winner);
  }
}

void Battle::AttackerTurn() {
  const auto attack_val = attacker_.Attack();
  defender_.TakeDamage(attack_val);
}

void Battle::DefenderTurn() {
  const auto attack_val = defender_.Attack();
  attacker_.TakeDamage(attack_val);
}

BattleWinner Battle::GetWinner() {
  if (!attacker_.IsAlive() && !defender_.IsAlive()) return BattleWinner::kDraw;
  else if (!attacker_.IsAlive()) return BattleWinner::kDefender;
  else if (!defender_.IsAlive()) return BattleWinner::kAttacker;
  else return BattleWinner::kNone;
}

void Battle::EndFight(BattleWinner winner) {
  attacker_.SetBattleState(BattleStates::kOutOfBattle);
  defender_.SetBattleState(BattleStates::kOutOfBattle);

  switch (winner) {
	case BattleWinner::kAttacker:
	  DistributeRewardsAfterFight(attacker_, defender_);
	  break;
	case BattleWinner::kDefender:
	  DistributeRewardsAfterFight(defender_, attacker_);
	  break;
	default:
	  break;
  }

  completed_ = true;
}

void Battle::DistributeRewardsAfterFight(IFightable &winner, IFightable &looser) {
  const auto looser_lvl = looser.GetLevel();
  winner.AddExperience(looser_lvl);
}





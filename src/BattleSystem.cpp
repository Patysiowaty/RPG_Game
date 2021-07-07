#include "BattleSystem.hpp"
void BattleSystem::StartBattle(IFightable *attacker, IFightable *defender) {
  if (!attacker || !defender) throw std::invalid_argument{"BattleSystem::StartBattle -> nullptr fighter!"};

  battles_list_.push_back(std::make_unique<Battle>(attacker, defender));
}

void BattleSystem::Update() {
  for (const auto &battle: battles_list_)
	battle->NextTurn();

  battles_list_.erase(std::remove_if(battles_list_.begin(),
									 battles_list_.end(),
									 [](const std::unique_ptr<Battle> &battle) { return battle->IsCompleted(); }),
					  battles_list_.end());
}

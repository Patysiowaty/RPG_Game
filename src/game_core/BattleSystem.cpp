#include "BattleSystem.hpp"
void BattleSystem::StartBattle(IFightable &attacker, IFightable &defender) {
  auto new_battle = std::make_unique<Battle>(attacker, defender);
  new_battle->InitializeBattle();
  battles_list_.push_back(std::move(new_battle));
}

void BattleSystem::Update(float delta_time) {
  for (const auto &battle: battles_list_)
	battle->NextTurn();

  battles_list_.erase(std::remove_if(battles_list_.begin(),
									 battles_list_.end(),
									 [](const std::unique_ptr<Battle> &battle) { return battle->IsCompleted(); }),
					  battles_list_.end());
}

#ifndef BATTLESYSTEM_HPP
#define BATTLESYSTEM_HPP
#include "Battle.hpp"
#include "../interfaces/IUpdatable.hpp"
#include <memory>
#include <vector>

class BattleSystem : public IUpdatable {
 public:

  void StartBattle(IFightable &attacker, IFightable &defender);
  void Update(float delta_time) override;

 private:
  std::vector<std::unique_ptr<Battle>> battles_list_;
};

#endif //BATTLESYSTEM_HPP

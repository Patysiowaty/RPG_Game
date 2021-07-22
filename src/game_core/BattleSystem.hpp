#ifndef BATTLESYSTEM_HPP
#define BATTLESYSTEM_HPP
#include "Battle.hpp"
#include <memory>
#include <vector>

class BattleSystem {
 public:

  void StartBattle(IFightable &attacker, IFightable &defender);
  void Update();

 private:
  std::vector<std::unique_ptr<Battle>> battles_list_;
};

#endif //BATTLESYSTEM_HPP

#ifndef GAMESTATESMANAGER_HPP
#define GAMESTATESMANAGER_HPP
#include <stack>
#include <vector>
#include <memory>
#include "interfaces/IGameState.hpp"

class GameStatesManager  {
 public:
  void PushState(std::unique_ptr<IGameState> game_state);
  void PopState();
  const std::unique_ptr<IGameState> &GetCurrentState();

 private:
  std::stack<std::unique_ptr<IGameState>> states_;
};

#endif //GAMESTATESMANAGER_HPP

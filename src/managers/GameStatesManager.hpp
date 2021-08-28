#ifndef GAMESTATESMANAGER_HPP
#define GAMESTATESMANAGER_HPP
#include <stack>
#include <vector>
#include <memory>
#include "../interfaces/IGameState.hpp"
#include "../interfaces/IPublisher.hpp"

class GameStatesManager {
 public:
  using GameStatesPtr = std::stack<std::shared_ptr<IGameState>>;

  void PushState(std::shared_ptr<IGameState> game_state);
  void PopState();
  void ClearStack();
  const GameStatesPtr &GetGameStatesPtr() const;

 private:
  GameStatesPtr states_;
};

#endif //GAMESTATESMANAGER_HPP

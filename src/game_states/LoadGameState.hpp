#ifndef LOADGAMESTATE_HPP
#define LOADGAMESTATE_HPP

#include "../interfaces/IGameState.hpp"
#include "../managers/GameStatesManager.hpp"
class LoadGameState : public IGameState {
 public:
  explicit LoadGameState(GameStatesManager &game_states_manager);
  void Initialize() override;
  void Render() override;
  void Update(float delta_time) override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;
  void Reload(const GameConfig &config) override;

 private:
  GameStatesManager &game_states_manager_;
};

#endif //LOADGAMESTATE_HPP

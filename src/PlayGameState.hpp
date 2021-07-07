#ifndef PLAYGAMESTATE_HPP
#define PLAYGAMESTATE_HPP
#include "interfaces/IGameState.hpp"
#include "Player.hpp"
#include "PlayerController.hpp"
#include "BattleSystem.hpp"
#include "GameStatesManager.hpp"

class PlayGameState : public IGameState {
 public:
  explicit PlayGameState(GameStatesManager &game_state_manager);
  void Initialize() override;
  void Draw(IViewContext *view_context, double delta_time) override;
  void Update(double delta_time) override;
  void HandleEvent() override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;

 private:
  GameStatesManager &game_states_manager_;
  bool active_{true};
  BattleSystem battle_system_;
  Player player_;
  PlayerController player_controller_;
};

#endif //PLAYGAMESTATE_HPP

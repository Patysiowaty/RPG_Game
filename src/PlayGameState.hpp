#ifndef PLAYGAMESTATE_HPP
#define PLAYGAMESTATE_HPP
#include "interfaces/IGameState.hpp"
#include "game_core/Player.hpp"
#include "game_core/PlayerController.hpp"
#include "game_core/BattleSystem.hpp"
#include "GameStatesManager.hpp"

class PlayGameState : public IGameState {
 public:
  explicit PlayGameState(GameStatesManager &game_state_manager);
  void Initialize() override;
  void Render(sf::RenderWindow &window) override;
  void Update(sf::Time delta_time) override;
  void HandleEvent(const sf::Event &event) override;
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

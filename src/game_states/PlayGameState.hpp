#ifndef PLAYGAMESTATE_HPP
#define PLAYGAMESTATE_HPP
#include "../interfaces/IGameState.hpp"
#include "../controllers/PlayerController.hpp"
#include "../game_core/BattleSystem.hpp"
#include "../managers/GameStatesManager.hpp"
#include "../game_core/PlayerCamera.hpp"
#include "../managers/WindowsManager.hpp"
#include "../managers/InputManager.hpp"
#include "../DrawableContainer.hpp"
#include "../GameLocation.hpp"

class PlayGameState : public IGameState {
 public:
  explicit PlayGameState(GameStatesManager &game_state_manager, sf::RenderWindow &render_window);
  void Initialize() override;
  void Render() override;
  void Update(float delta_time) override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;
  void Reload(const GameConfig &config) override;

 private:
  void RegisterHandlers();
  void SetObjectsPosition();
  void LoadTextures();
  void LoadGameData();
  void ReadConfigs();

 private:
  bool active_{true};
  GameStatesManager &game_states_manager_;
  sf::RenderWindow &render_window_;

  BattleSystem battle_system_;
  Player player_;
  PlayerView player_view_;
  PlayerController player_controller_;

  GameLocation current_player_location_;

  PlayerCamera game_camera_;
  WindowsManager windows_manager_;
  DrawableContainer drawable_container_;

  std::list<IUpdatable *> updatable_list_;
};

#endif //PLAYGAMESTATE_HPP

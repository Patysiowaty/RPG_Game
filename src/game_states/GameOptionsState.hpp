#ifndef GAMEOPTIONSSTATE_HPP
#define GAMEOPTIONSSTATE_HPP

#include "../interfaces/IGameState.hpp"
#include "../managers/GameStatesManager.hpp"
#include "../ui_elements/Button.hpp"

class GameOptionsState : public IGameState {
 public:
  explicit GameOptionsState(GameStatesManager &game_states_manager, sf::RenderWindow &render_window);
  void Initialize() override;
  void Render() override;
  void Update(float delta_time) override;
  void Reload(const GameConfig &game_config) override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;

 private:
  bool active_{true};
  GameStatesManager &game_states_manager_;
  sf::RenderWindow &render_window_;

  sf::Font game_option_font_;
  Button return_button_;
};

#endif //GAMEOPTIONSSTATE_HPP

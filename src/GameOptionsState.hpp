#ifndef GAMEOPTIONSSTATE_HPP
#define GAMEOPTIONSSTATE_HPP

#include "interfaces/IGameState.hpp"
#include "GameStatesManager.hpp"
#include "Button.hpp"
#include "EventDispatcher.hpp"

class GameOptionsState : public IGameState {
 public:
  explicit GameOptionsState(GameStatesManager &game_states_manager);
  void Initialize() override;
  void Render(sf::RenderWindow &window) override;
  void Update(sf::Time delta_time) override;
  void HandleEvent(const sf::Event &event) override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;

 private:
  bool active_{true};
  GameStatesManager &game_states_manager_;

  EventDispatcher event_dispatcher_;

  sf::Font game_option_font_;
  Button return_button_;
};

#endif //GAMEOPTIONSSTATE_HPP

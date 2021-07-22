#ifndef MENUGAMESTATE_HPP
#define MENUGAMESTATE_HPP

#include "interfaces/IGameState.hpp"
#include "GameStatesManager.hpp"
#include "EventDispatcher.hpp"
#include "Button.hpp"
class MenuGameState : public IGameState {
 public:
  explicit MenuGameState(GameStatesManager &game_states_manager);
  void Initialize() override;
  void Render(sf::RenderWindow &window) override;
  void Update(sf::Time delta_time) override;
  void HandleEvent(const sf::Event &event) override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;

 private:
  bool active_{true};
  sf::Font menu_state_font_;
  Button start_game_button_;
  Button load_game_button_;
  Button game_option_button_;
  Button quit_game_button_;

  GameStatesManager &game_states_manager_;
  EventDispatcher event_dispatcher_;
};

#endif //MENUGAMESTATE_HPP

#ifndef MENUGAMESTATE_HPP
#define MENUGAMESTATE_HPP

#include "../interfaces/IGameState.hpp"
#include "../managers/GameStatesManager.hpp"
#include "../ui_elements/Button.hpp"
#include <list>

class MenuGameState : public IGameState {
 public:
  explicit MenuGameState(GameStatesManager &game_states_manager, sf::RenderWindow &render_window);
  void Initialize() override;
  void Render() override;
  void Update(float delta_time) override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;
  void Reload(const GameConfig &config) override;

 private:
  void RegisterCommands();
  void BindElements();
  void ReadConfigs();

 private:
  bool active_{true};
  GameStatesManager &game_states_manager_;
  sf::RenderWindow &render_window_;

  Button start_game_;
  Button load_game_;
  Button game_options_;
  Button quit_game_;

  std::list<sf::Drawable *> drawable_list_;
  std::list<IUpdatable *> updatables_list_;

};

#endif //MENUGAMESTATE_HPP

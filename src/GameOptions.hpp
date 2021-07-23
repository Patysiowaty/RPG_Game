#ifndef GAMEOPTIONS_HPP
#define GAMEOPTIONS_HPP

#include "interfaces/IGameState.hpp"
#include "GameStatesManager.hpp"

class GameOptions : public IGameState {
 public:
  explicit GameOptions(GameStatesManager &game_states_manager);
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
};

#endif //GAMEOPTIONS_HPP

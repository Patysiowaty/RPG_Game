#ifndef LOADGAMESTATE_HPP
#define LOADGAMESTATE_HPP

#include "interfaces/IGameState.hpp"
#include "GameStatesManager.hpp"
#include "EventDispatcher.hpp"
class LoadGameState : public IGameState {
 public:
  explicit LoadGameState(GameStatesManager &game_states_manager);
  void Initialize() override;
  void Render(sf::RenderWindow &window) override;
  void Update(sf::Time delta_time) override;
  void HandleEvent(const sf::Event &event) override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;

 private:
  GameStatesManager &game_states_manager_;
  EventDispatcher event_dispatcher_;
};

#endif //LOADGAMESTATE_HPP

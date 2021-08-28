#ifndef IGAMESTATE_HPP
#define IGAMESTATE_HPP
#include <SFML/Graphics.hpp>
#include "../game_core/GameConfig.hpp"

class IGameState {
 public:
  virtual ~IGameState() = default;
  virtual void Initialize() = 0;
  virtual void Render() = 0;
  virtual void Update(float delta_time) = 0;
  virtual void Reload(const GameConfig &config) = 0;
  virtual void Cleanup() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;
};

#endif //IGAMESTATE_HPP

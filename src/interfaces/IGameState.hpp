#ifndef IGAMESTATE_HPP
#define IGAMESTATE_HPP
#include <SFML/Graphics.hpp>

class IGameState {
 public:
  virtual ~IGameState() = default;
  virtual void Initialize() = 0;
  virtual void Render(sf::RenderWindow &window) = 0;
  virtual void Update(sf::Time delta_time) = 0;
  virtual void HandleEvent(const sf::Event &event) = 0;
  virtual void Cleanup() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;
};

#endif //IGAMESTATE_HPP

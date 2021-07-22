#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

#include <SFML/Window/Event.hpp>
class IEventHandler {
 public:
  virtual void OnMouseMove(const sf::Event &event) = 0;
  virtual void OnMouseDown(const sf::Event &event) = 0;
  virtual void OnMouseUp(const sf::Event &event) = 0;
  virtual void OnKeyDown(const sf::Event &event) = 0;
  virtual void OnKeyUp(const sf::Event &event) = 0;
  virtual void OnMouseScroll(const sf::Event &event) = 0;
};

#endif //IEVENTHANDLER_HPP

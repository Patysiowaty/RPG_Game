#ifndef PLAYERCAMERA_HPP
#define PLAYERCAMERA_HPP

#include <SFML/Graphics/View.hpp>
#include "../interfaces/IPlayerHandler.hpp"

class PlayerCamera : public sf::View, public IPlayerHandler {
 public:
  void OnPlayerMove(const sf::Vector2<float> &offset) override;
};

#endif //PLAYERCAMERA_HPP

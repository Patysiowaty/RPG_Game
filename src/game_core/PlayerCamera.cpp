#include "PlayerCamera.hpp"
void PlayerCamera::OnPlayerMove(const sf::Vector2<float> &offset) {
  sf::View::move(offset);
}


#include "PlayerViewWindow.hpp"
PlayerViewWindow::PlayerViewWindow() {
  player_view_.CreateSprite("../resources/graphics/player.png");
}

void PlayerViewWindow::Update(float delta_time) {
  Window::Update(delta_time);
  player_view_.Update(delta_time);
  player_view_.OnMoveDown({0, 0});
}

void PlayerViewWindow::SetRelativeViewPosition(const sf::Vector2f &new_position) {
  relative_view_position_ = new_position;
}

void PlayerViewWindow::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!IsActive()) return;
  Window::draw(target, states);
  target.draw(player_view_, states);
}

void PlayerViewWindow::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
  player_view_.Move(offset);
}

void PlayerViewWindow::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);
  player_view_.SetPosition(new_position + relative_view_position_);
}

void PlayerViewWindow::EquipItem(const std::shared_ptr<Item> &item) {
  player_view_.OnEquipItem(item);
}

void PlayerViewWindow::TakeOffItem(ItemType item_type) {
  player_view_.OnTakeOffItem(item_type);
}



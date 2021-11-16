#include "PlayerViewWindow.hpp"
PlayerViewWindow::PlayerViewWindow() {
  player_view_.CreateSprite("../resources/graphics/player.png");
  animation_list_.emplace_back(AnimationType::kWalkDown);
  animation_list_.emplace_back(AnimationType::kWalkRight);
  animation_list_.emplace_back(AnimationType::kWalkUp);
  animation_list_.emplace_back(AnimationType::kWalkLeft);
}

void PlayerViewWindow::Update(float delta_time) {
  Window::Update(delta_time);
  const auto animation = animation_list_.at(current_animation_index_);
  player_view_.PlayAnimation(animation, true);
  player_view_.Update(delta_time);
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

void PlayerViewWindow::NextAnimation() {
  const std::int16_t kMaxAnimationIndex = animation_list_.size() - 1;
  const std::int16_t kNextAnimationIndex = ++current_animation_index_;

  current_animation_index_ = kNextAnimationIndex > kMaxAnimationIndex ? 0 : kNextAnimationIndex;
}

void PlayerViewWindow::PreviousAnimation() {
  const std::int16_t kNextAnimationIndex = --current_animation_index_;
  const std::int16_t kMaxAnimationIndex = animation_list_.size() - 1;

  current_animation_index_ = kNextAnimationIndex < 0 ? kMaxAnimationIndex : kNextAnimationIndex;
}



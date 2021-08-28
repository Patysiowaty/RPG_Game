#include "PlayerView.hpp"

PlayerView::PlayerView(const std::string &texture_path) {
  CreateSprite(texture_path);
  CreateAnimations();
  animation_controller_.SetActive(AnimationType::kWalkDown);
}

void PlayerView::CreateSprite(const std::string &texture_path) {
  if (!texture_.loadFromFile(texture_path))
	throw std::invalid_argument{"PlayerView::CreateSprite -> failed load texture: " + texture_path};
  texture_.setSmooth(true);

  PlayerView::CreateAnimations();
  animation_controller_.SetActive(AnimationType::kWalkDown);
}

void PlayerView::SetPosition(float x, float y) {
  sf::Transformable::setPosition(x, y);
  sprite_.setPosition(sf::Transformable::getPosition());
}

void PlayerView::Update(float delta_time) {
  animation_controller_.Update(delta_time);
}

void PlayerView::CreateAnimations() {
  const auto[kTotalWidth, kTotalHeight] = texture_.getSize();

  animation_controller_.AddAnimation(AnimationType::kWalkDown, Animation{texture_, sprite_,
																		 FrameDetails{sf::IntRect(0, 0, kTotalWidth,
																								  kTotalHeight / 4)}});
  animation_controller_.AddAnimation(AnimationType::kWalkLeft, Animation{texture_, sprite_,
																		 FrameDetails{
																			 sf::IntRect(0,
																						 1 * kTotalHeight / 4,
																						 kTotalWidth,
																						 kTotalHeight / 4)}});
  animation_controller_.AddAnimation(AnimationType::kWalkRight, Animation{texture_, sprite_,
																		  FrameDetails{
																			  sf::IntRect(0,
																						  2 * kTotalHeight / 4,
																						  kTotalWidth,
																						  kTotalHeight / 4)}});
  animation_controller_.AddAnimation(AnimationType::kWalkUp, Animation{texture_, sprite_,
																	   FrameDetails{
																		   sf::IntRect(0,
																					   3 * kTotalHeight / 4,
																					   kTotalWidth,
																					   kTotalHeight / 4)}});
}

void PlayerView::MoveUp(const sf::Vector2f &offset) {
  sprite_.move(offset);
  animation_controller_.SetActive(AnimationType::kWalkUp);
}

void PlayerView::MoveDown(const sf::Vector2f &offset) {
  sprite_.move(offset);
  animation_controller_.SetActive(AnimationType::kWalkDown);
}

void PlayerView::MoveLeft(const sf::Vector2f &offset) {
  sprite_.move(offset);
  animation_controller_.SetActive(AnimationType::kWalkLeft);
}

void PlayerView::MoveRight(const sf::Vector2f &offset) {
  sprite_.move(offset);
  animation_controller_.SetActive(AnimationType::kWalkRight);
}

void PlayerView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= sprite_.getTransform();
  target.draw(sprite_);
}




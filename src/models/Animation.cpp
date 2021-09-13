#include "Animation.hpp"
Animation::Animation(sf::Texture &texture, sf::Sprite &sprite, const AnimationDetails &details) : texture_{texture},
																								  sprite_{sprite},
																								  details_{details} {
  for (int i = 0; i < details_.number_of_frames; ++i) {
	animation_frames_.emplace_back(i * (details_.size.width / details_.number_of_frames), details_.size.top,
								   details_.size.width / details.number_of_frames, details_.size.height);
  }
}

void Animation::Update(float delta_time) {
  current_time_ += delta_time;
  while (current_time_ >= kHoldTime) {
	current_time_ -= kHoldTime;
	NextFrame();
  }
}

void Animation::Start() {
  run_ = true;
  stop_ = false;
  steps_left_ = details_.animation_step;
  current_frame_ = 0;
  NextFrame();
}

void Animation::Stop() {
  run_ = false;
  stop_ = true;
  current_frame_ = details_.looped_first_frame;
  Apply();
}

void Animation::Play() {
  run_ = true;
  steps_left_ = details_.animation_step;
}

void Animation::NextFrame() {
  if (run_) {
	current_frame_++;

  if (current_frame_ >= details_.number_of_frames) {
	Stop();
	return;
  }

  Apply();
}

void Animation::Apply() {
  sprite_.setTexture(texture_);
  sprite_.setTextureRect(frame_row_.at(current_frame_));
}

void Animation::LockAnimation() {
  locked_ = true;
}

void Animation::Pause() {
  run_ = false;
}

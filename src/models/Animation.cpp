#include "Animation.hpp"
Animation::Animation(sf::Texture &texture, sf::Sprite &sprite, const FrameDetails &details) : texture_{texture},
																							  sprite_{sprite},
																							  details_{details} {
  for (int i = 0; i < details_.number_of_frames; ++i) {
	frame_row_.emplace_back(i * (details_.size_.width / details_.number_of_frames), details_.size_.top,
							details_.size_.width / details.number_of_frames, details_.size_.height);
  }
}

void Animation::Update(float delta_time) {
  current_time_ += delta_time;
  while (current_time_ >= kHoldTime) {
	current_time_ -= kHoldTime;
	NextFrame();
  }
}

void Animation::Activate() {
  StartAnimation();
  NextFrame();
}

void Animation::StopAnimation() {
  run_ = false;
  current_frame_ = 0;
}

void Animation::StartAnimation() {
  run_ = true;
  current_frame_ = 0;
}

void Animation::NextFrame() {
  if (run_)
	current_frame_++;

  if (current_frame_ >= details_.number_of_frames) {
	StopAnimation();
	if (locked_)
	  UnlockAnimation();
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

void Animation::UnlockAnimation() {
  locked_ = false;
}

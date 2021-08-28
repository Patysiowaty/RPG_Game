#include "AnimationsController.hpp"

void AnimationsController::Update(float delta_time) {
  if (!current_animation_) return;
  current_animation_->Update(delta_time);
}

void AnimationsController::AddAnimation(AnimationType animation_type, const Animation &animations) {
  if (const auto it = animations_list_.find(animation_type); it != animations_list_.end())
	throw std::invalid_argument{"AnimationsController::AddAnimation -> animation " +
		std::to_string(static_cast<int>(animation_type)) + " already exists"};

  animations_list_.emplace(animation_type, animations);
}

void AnimationsController::SetActive(AnimationType animation_type) {
  if (const auto it = animations_list_.find(animation_type); it == animations_list_.end())
	throw std::invalid_argument{"AnimationsController::SetActive -> animation " +
		std::to_string(static_cast<int>(animation_type)) + " not found!"};

  if (current_animation_ != &animations_list_.at(animation_type)) {
	current_animation_ = &animations_list_.at(animation_type);
	current_animation_->Activate();
  }
  if (!current_animation_->IsRunning())
	current_animation_->StartAnimation();
}



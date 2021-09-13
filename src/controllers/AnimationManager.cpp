#include "AnimationManager.hpp"

AnimationManager::AnimationManager() = default;

void AnimationManager::AddAnimation(AnimationType animation_type, sf::Sprite &sprite, sf::Texture &texture,
									const AnimationDetails &animation_details) {
  animations_list_.emplace(animation_type, Animation{texture, sprite, animation_details});
}

void AnimationManager::PlayAnimation(AnimationType animation_type) {
  if (current_animation_ == animation_type) {
	for (auto &animation: animations_list_)
	  animation.second.Play();
	return;
  }

  if (const auto it = animations_list_.find(animation_type); it == animations_list_.end())
	throw std::invalid_argument{"AnimationManager::PlayAnimation -> animation " +
		std::to_string(static_cast<int>(animation_type)) + " not found!"};

  AnimationManager::ClearActiveList();

  const auto &range = animations_list_.equal_range(animation_type);
  for (auto it = range.first; it != range.second; ++it) {
	it->second.Start();
	it->second.Play();
	playing_animation_.push_back(&it->second);
  }
  current_animation_ = animation_type;
}

void AnimationManager::Update(float delta_time) {
  int counter{0};
  for (auto &animation : playing_animation_) {
	animation->Update(delta_time);

	if (!animation->IsRunning())
	  counter++;
  }

  if (counter == playing_animation_.size()) {
	ClearActiveList();
	current_animation_ = AnimationType::kNone;
  }

}

void AnimationManager::ClearActiveList() {
  if (playing_animation_.empty()) return;

  for (auto &animation: playing_animation_) {
	animation->Stop();
  }
  playing_animation_.clear();
}



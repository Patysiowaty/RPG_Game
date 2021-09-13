#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "../models/Animation.hpp"
#include "../enums/AnimationState.hpp"
#include "../AnimationDetails.hpp"
#include <memory>
#include <list>

enum class AnimationType {
  kNone,
  kIdle,
  kWalkUp,
  kWalkDown,
  kWalkLeft,
  kWalkRight,
  kSlashAttackUp,
  kSlashAttackDown,
  kSlashAttackLeft,
  kSlashAttackRight,
};

class AnimationManager {
 public:
  explicit AnimationManager();
  void AddAnimation(AnimationType animation_type, sf::Sprite &sprite, sf::Texture &texture,
					const AnimationDetails &animation_details);
  void PlayAnimation(AnimationType animation_type);
  void Update(float delta_time);
  AnimationType GetCurrentAnimation() const { return current_animation_; }
  void ClearActiveList();

 private:
  std::multimap<AnimationType, Animation> animations_list_;
  std::list<Animation *> playing_animation_;
  AnimationType current_animation_{AnimationType::kNone};
};

#endif //ANIMATIONMANAGER_HPP

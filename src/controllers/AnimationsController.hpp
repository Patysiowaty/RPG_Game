#ifndef ANIMATIONSCONTROLLER_HPP
#define ANIMATIONSCONTROLLER_HPP

#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "../models/Animation.hpp"
#include "../enums/AnimationState.hpp"
#include "../FrameDetails.hpp"

enum class AnimationType {
  kNone, kIdle, kWalkUp, kWalkDown, kWalkLeft, kWalkRight, kAttack
};

class AnimationsController {
 public:
  AnimationsController() = default;
  void Update(float delta_time);
  void AddAnimation(AnimationType animation_type, const Animation &animations);
  void SetActive(AnimationType animation_type);

 private:
  Animation *current_animation_{nullptr};
  std::map<AnimationType, Animation> animations_list_;
  AnimationState animation_state_{AnimationType::kNone};
};

#endif //ANIMATIONSCONTROLLER_HPP

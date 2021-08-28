#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "../FrameDetails.hpp"

class Animation {
 public:
  Animation(sf::Texture &texture, sf::Sprite &sprite, const FrameDetails &details);

  void Update(float delta_time);

  void Activate();
  void StopAnimation();
  void StartAnimation();
  void LockAnimation();
  void UnlockAnimation();

  bool IsLocked() const { return locked_; }
  bool IsRunning() const { return run_; }

 private:
  void NextFrame();
  void Apply();

 private:
  constexpr static float kHoldTime{0.2};

  sf::Texture &texture_;
  sf::Sprite &sprite_;

  FrameDetails details_;
  std::vector<sf::IntRect> frame_row_;

  std::int16_t current_frame_{0};
  float current_time_{0.f};
  bool run_{true};
  bool locked_{true};
};

#endif //ANIMATION_HPP

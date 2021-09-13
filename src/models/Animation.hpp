#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <cstdint>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "../AnimationDetails.hpp"

class Animation {
 public:
  Animation(sf::Texture &texture, sf::Sprite &sprite, const AnimationDetails &details);

  void Update(float delta_time);

  void Start();
  void Stop();
  void Play();
  void Pause();

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

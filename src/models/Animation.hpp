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
  bool IsStopped() const { return stop_; }

 private:
  void NextFrame();
  void Apply();

 private:

  sf::Texture &texture_;
  sf::Sprite &sprite_;

  AnimationDetails details_;
  std::vector<sf::IntRect> animation_frames_;

  float hold_time_{.0f};
  float current_time_{.0f};
  bool run_{false};
  bool stop_{false};

  std::int16_t steps_left_{0};
  std::int16_t current_frame_{0};
};

#endif //ANIMATION_HPP

#ifndef ANIMATIONDETAILS_HPP
#define ANIMATIONDETAILS_HPP
struct AnimationDetails {
  const sf::IntRect size;
  const std::int16_t number_of_frames;
  const std::int16_t animation_step;
  const std::int16_t looped_first_frame{0};
  const float frame_time{0.12f};
};
#endif //ANIMATIONDETAILS_HPP

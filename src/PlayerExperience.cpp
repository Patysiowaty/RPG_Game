#include "PlayerExperience.hpp"

#include <stdexcept>
#include <string>
#include <cmath>

PlayerExperience::PlayerExperience(size_t total_experience, size_t next_level_experience) :
	total_experience_{total_experience}, next_level_experience_{next_level_experience} {
}

void PlayerExperience::AddExperience(int32_t value) {
  if (!IsValidExperience(value))
	throw std::invalid_argument{"PlayerExperience::AddExperience -> value: " + std::to_string(value)};

  total_experience_ += value;
}

bool PlayerExperience::IsValidExperience(int32_t value) const {
  return value >= 0;
}

void PlayerExperience::CalculateNextLevelExperience(std::uint16_t value) {
  const auto player_level_modifier = value * 100;
  next_level_experience_ = static_cast<size_t>(std::pow(player_level_modifier, 2) / 100);
}

bool PlayerExperience::ShouldLevelUp() const {
  return total_experience_ >= next_level_experience_;
}

void PlayerExperience::ShrinkToFit() {
  total_experience_ = next_level_experience_;
}

double PlayerExperience::GetNextLevelPercentProgress() const {
  return static_cast<double>(total_experience_) / static_cast<double>(next_level_experience_);
}




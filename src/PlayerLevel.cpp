#include "PlayerLevel.hpp"
#include <cmath>

PlayerLevel::PlayerLevel(std::uint16_t level, std::size_t total_exp) {
  SetLevel(level);
  SetExperience(total_exp);
}

void PlayerLevel::AddExperience(int32_t value) {
  total_experience_ += value;

  while (total_experience_ >= next_level_experience_) {
	if (LevelUp()) {
	  CalculateNextLevelExperience();
	  for (auto handler: handlers_) {
		handler->OnLevelRaise();
	  }
	} else {
	  total_experience_ = next_level_experience_;
	  break;
	}
  }
}

void PlayerLevel::RegisterHandler(ILevelHandler *level_handler) {
  handlers_.push_back(level_handler);
}

void PlayerLevel::SetExperience(std::size_t value) {
  total_experience_ = value;

  while (total_experience_ >= next_level_experience_) {
	if (LevelUp()) {
	  CalculateNextLevelExperience();
	  for (auto handler: handlers_) {
		handler->OnLevelRaise();
	  }
	} else {
	  total_experience_ = next_level_experience_;
	  break;
	}
  }
}

std::uint16_t PlayerLevel::GetLevel() const {
  return level_;
}

void PlayerLevel::SetLevel(uint16_t value) {
  const auto old_level = level_;

  level_ = value > kLevelCap ? kLevelCap : value;

  total_experience_ = CalculateNextLevelExperience(level_ - 1);
  next_level_experience_ =
	  level_ >= kLevelCap ? CalculateNextLevelExperience(level_ - 1) : CalculateNextLevelExperience(level_);

  for (const auto handler: handlers_)
	handler->OnLevelUpdate(level_ - old_level);
}

bool PlayerLevel::HasMaximumLevel() const {
  return level_ >= kLevelCap;
}

bool PlayerLevel::LevelUp() {
  if (!HasMaximumLevel()) {
	level_++;
	return true;
  }
  return false;
}

size_t PlayerLevel::CalculateNextLevelExperience() {
  return CalculateNextLevelExperience(level_);
}

size_t PlayerLevel::CalculateNextLevelExperience(std::uint16_t value) {
  const auto player_level_modifier = value * 100;
  return static_cast<size_t>(std::pow(player_level_modifier, 2) / 100);
}

std::pair<size_t, size_t> PlayerLevel::GetExperience() const {
  return std::make_pair(total_experience_, next_level_experience_);
}

double PlayerLevel::GetExperiencePercent() const {
  return static_cast<double>(total_experience_) / static_cast<double>(next_level_experience_);
}





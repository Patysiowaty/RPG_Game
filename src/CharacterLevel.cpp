#include "CharacterLevel.hpp"

CharacterLevel::CharacterLevel(std::uint16_t level) {
  SetLevel(level);
}

bool CharacterLevel::LevelUp() {
  if (!HasMaximumLevel()) {
	level_++;
	return true;
  }
  return false;
}

void CharacterLevel::SetLevel(uint16_t value) {
  if (value <= level_cap_)
	level_ = value;
}

bool CharacterLevel::HasMaximumLevel() const {
  return level_ >= level_cap_;
}





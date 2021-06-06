#include "CharacterStatistics.hpp"
#include "Character.hpp"

CharacterStatistics::CharacterStatistics() {

}

void CharacterStatistics::SetAttack(std::int32_t value) {
  attack_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::AddAttack(std::int32_t value) {
  if (value < 0) return SubtractAttack(-value);
  attack_ = (attack_ + value) > kMaxStatValue ? kMaxStatValue : attack_ + value;

}

void CharacterStatistics::SubtractAttack(std::int32_t value) {
  if (value < 0) return AddAttack(-value);
  attack_ = (attack_ - value) < 0 ? 0 : attack_ - value;

}

void CharacterStatistics::RecalculateAttack(std::int32_t value) {

}

void CharacterStatistics::SetHealth(std::int32_t value) {
  health_ = value < 0 ? 0 : value > max_health_ ? max_health_ : value;
}

void CharacterStatistics::RecoverHealth(std::int32_t value) {
  if (value < 0) return SubtractHealth(-value);

  health_ = (health_ + value) > max_health_ ? max_health_ : health_ + value;

}

void CharacterStatistics::SubtractHealth(std::int32_t value) {
  if (value < 0) return RecoverHealth(-value);
  if (health_ - value <= 0) {
	health_ = 0;

  } else {
	health_ -= value;

  }
}

void CharacterStatistics::SetMaxHealth(std::int32_t value) {
  max_health_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::IncreaseMaxHealth(std::int32_t value) {
  if (value < 0) return DecreaseMaxHealth(-value);

  max_health_ = (max_health_ + value) > kMaxStatValue ? kMaxStatValue : max_health_ + value;
}

void CharacterStatistics::DecreaseMaxHealth(std::int32_t value) {
  if (value < 0) return IncreaseMaxHealth(-value);

  max_health_ = (max_health_ - value) < 0 ? 0 : max_health_ - value;

  if (health_ > max_health_) SubtractHealth(health_ - max_health_);

}

void CharacterStatistics::RecalculateMaxHealth(std::int32_t value) {

}

void CharacterStatistics::SetStamina(std::int32_t value) {
  stamina_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::RecoverStamina(std::int32_t value) {
  if (value < 0) return SubtractStamina(-value);

  stamina_ = (stamina_ + value) > kMaxStatValue ? kMaxStatValue : stamina_ + value;

}

void CharacterStatistics::SubtractStamina(std::int32_t value) {
  if (value < 0) return RecoverStamina(-value);

  stamina_ = (stamina_ - value) < 0 ? 0 : stamina_ - value;

}

void CharacterStatistics::SetMaxStamina(std::int32_t value) {
  max_stamina_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::IncreaseMaxStamina(std::int32_t value) {
  if (value < 0) return DecreaseMaxStamina(-value);

  max_stamina_ = (max_stamina_ + value) > kMaxStatValue ? kMaxStatValue : max_stamina_ + value;
}

void CharacterStatistics::DecreaseMaxStamina(std::int32_t value) {
  if (value < 0) return IncreaseMaxStamina(-value);

  max_stamina_ = (max_stamina_ - value) < 0 ? 0 : max_stamina_ - value;

  if (stamina_ > max_stamina_) SubtractHealth(stamina_ - max_stamina_);

}

void CharacterStatistics::RecalculateMaxStamina(std::int32_t value) {

}

void CharacterStatistics::SetMana(std::int32_t value) {
  mana_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::RecoverMana(std::int32_t value) {
  if (value < 0) return SubtractMana(-value);

  mana_ = (mana_ + value) > kMaxStatValue ? kMaxStatValue : mana_ + value;

}

void CharacterStatistics::SubtractMana(std::int32_t value) {
  if (value < 0) return RecoverMana(-value);

  mana_ = (mana_ - value) < 0 ? 0 : mana_ - value;

}

void CharacterStatistics::SetMaxMana(std::int32_t value) {
  max_mana_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::IncreaseMaxMana(std::int32_t value) {
  if (value < 0) return DecreaseMaxMana(-value);

  max_mana_ = (max_mana_ + value) > kMaxStatValue ? kMaxStatValue : max_mana_ + value;
}

void CharacterStatistics::DecreaseMaxMana(std::int32_t value) {
  if (value < 0) return IncreaseMaxMana(-value);

  max_mana_ = (max_mana_ - value) < 0 ? 0 : max_mana_ - value;

  if (mana_ > max_mana_) SubtractHealth(mana_ - max_mana_);

}

void CharacterStatistics::RecalculateMaxMana(std::int32_t value) {

}

void CharacterStatistics::SetArmor(std::int32_t value) {
  armor_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::AddArmor(std::int32_t value) {
  if (value < 0) return SubtractArmor(-value);

  armor_ = (armor_ + value) > kMaxStatValue ? kMaxStatValue : armor_ + value;

}

void CharacterStatistics::SubtractArmor(std::int32_t value) {
  if (value < 0) return AddArmor(-value);

  armor_ = (armor_ - value) < 0 ? 0 : armor_ - value;

}

void CharacterStatistics::SetMaxArmor(std::int32_t value) {
  max_armor_ = value < 0 ? 0 : value > kMaxStatValue ? kMaxStatValue : value;
}

void CharacterStatistics::IncreaseMaxArmor(std::int32_t value) {
  if (value < 0) return DecreaseMaxArmor(-value);

  max_armor_ = (max_armor_ + value) > kMaxStatValue ? kMaxStatValue : max_armor_ + value;
}

void CharacterStatistics::DecreaseMaxArmor(std::int32_t value) {
  if (value < 0) return IncreaseMaxArmor(-value);

  max_armor_ = (max_armor_ - value) < 0 ? 0 : max_armor_ - value;

  if (armor_ > max_armor_) SubtractHealth(armor_ - max_armor_);
}

















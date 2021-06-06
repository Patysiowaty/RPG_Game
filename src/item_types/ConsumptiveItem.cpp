#include "ConsumptiveItem.hpp"
ConsumptiveItem::ConsumptiveItem() {

}

void ConsumptiveItem::SetHealthRegen(std::int32_t value) {
  health_regen_ = std::make_unique<std::int32_t>(value);
}

int32_t ConsumptiveItem::GetHealthRegen() const {
  return health_regen_ ? *health_regen_ : 0;
}

void ConsumptiveItem::SetManaRegen(std::int32_t value) {
  mana_regen_ = std::make_unique<std::int32_t>(value);
}

int32_t ConsumptiveItem::GetManaRegen() const {
  return mana_regen_ ? *mana_regen_ : 0;
}

void ConsumptiveItem::SetStaminaRegen(std::int32_t value) {
  stamina_regen_ = std::make_unique<std::int32_t>(value);
}

std::int32_t ConsumptiveItem::GetStaminaRegen() const {
  return stamina_regen_ ? *stamina_regen_ : 0;
}

void ConsumptiveItem::SetAdditionalHealthMax(std::int32_t value) {
  additional_health_max_ = std::make_unique<std::int32_t>(value);
}

std::int32_t ConsumptiveItem::GetAdditionalHealthMax() const {
  return additional_health_max_ ? *additional_health_max_ : 0;
}

void ConsumptiveItem::SetAdditionalStamina(std::int32_t value) {
  additional_stamina_ = std::make_unique<std::int32_t>(value);
}

std::int32_t ConsumptiveItem::GetAdditionalStamina() const {
  return additional_stamina_ ? *additional_stamina_ : 0;
}

void ConsumptiveItem::SetAdditionalMana(std::int32_t value) {
  additional_mana_ = std::make_unique<std::int32_t>(value);
}

std::int32_t ConsumptiveItem::GetAdditionalMana() const {
  return additional_mana_ ? *additional_mana_ : 0;
}







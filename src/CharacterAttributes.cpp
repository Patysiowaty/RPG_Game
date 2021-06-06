#include "CharacterAttributes.hpp"
#include "Character.hpp"
#include <stdexcept>
CharacterAttributes::CharacterAttributes() {

}

void CharacterAttributes::SetStrength(const int32_t strength) {
  strength_ = strength;
}

void CharacterAttributes::SetDexterity(const int32_t dexterity) {
  dexterity_ = dexterity;
}

void CharacterAttributes::SetVitality(const int32_t vitality) {
  vitality_ = vitality;
}

void CharacterAttributes::SetIntelligence(const int32_t intelligence) {
  intelligence_ = intelligence;
}

void CharacterAttributes::SetAttributes(const int32_t strength, const int32_t dexterity, const int32_t vitality,
										const int32_t intelligence) {
  SetStrength(strength);
  SetDexterity(dexterity);
  SetVitality(vitality);
  SetIntelligence(intelligence);
}

void CharacterAttributes::SetBaseAttributes(const int32_t strength, const int32_t dexterity, const int32_t vitality,
											const int32_t intelligence) {
  base_strength_ = strength;
  base_dexterity_ = dexterity;
  base_vitality_ = vitality;
  base_intelligence_ = intelligence;
}

void CharacterAttributes::AddStrength(const int32_t value) {
  strength_ += value;
}

void CharacterAttributes::AddDexterity(const int32_t value) {
  dexterity_ += value;
}

void CharacterAttributes::AddVitality(const int32_t value) {
  vitality_ += value;
}

void CharacterAttributes::AddIntelligence(const int32_t value) {
  intelligence_ += value;
}

void CharacterAttributes::SubtractStrength(const int32_t value) {
  strength_ -= value;
}

void CharacterAttributes::SubtractDexterity(const int32_t value) {
  dexterity_ -= value;
}

void CharacterAttributes::SubtractVitality(const int32_t value) {
  vitality_ -= value;
}

void CharacterAttributes::SubtractIntelligence(const int32_t value) {
  intelligence_ -= value;
}

void CharacterAttributes::RaiseBaseAttributes() {
  base_strength_ += 3;
  base_dexterity_ += 3;
  base_vitality_ += 3;
  base_intelligence_ += 3;
}

void CharacterAttributes::OnLevelUpdate() {
  RaiseBaseAttributes();
}










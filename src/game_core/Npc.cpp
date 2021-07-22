#include "Npc.hpp"

NPC::NPC() {

}

void NPC::SetName(const std::string &value) {
  name_ = value;
}

void NPC::SetId(uint32_t value) {
  id_ = value;
}

void NPC::SetGender(CharacterGender value) {
  gender_ = value;
}

void NPC::SetRace(CharacterRace value) {
  race_ = value;
}

void NPC::SetClass(CharacterClass value) {
  class_ = value;
}

const std::string &NPC::GetName() const {
  return name_;
}

uint32_t NPC::GetId() const {
  return id_;
}

boost::uuids::uuid NPC::GetUuid() const {
  return uuid_;
}

CharacterClass NPC::GetClass() const {
  return class_;
}

CharacterGender NPC::GetGender() const {
  return gender_;
}

CharacterRace NPC::GetRace() const {
  return race_;
}

std::int32_t NPC::Attack() const {
  const auto &attack = character_statistics_list_.GetStatistic(StatisticType::kAttack);
  const auto attack_min = attack->GetValue();
  const auto attack_max = attack->GetMaxValue();

  return std::rand() % (attack_max - attack_min) + attack_min;
}

void NPC::TakeDamage(std::int32_t value) {
  const auto &health = character_statistics_list_.GetStatistic(StatisticType::kHealth);
  health->SubtractValue(value);
  if (health->GetValue() == 0)
	alive_ = false;
}

std::int32_t NPC::GetCurrentHealth() const {
  return character_statistics_list_.GetStatistic(StatisticType::kHealth)->GetValue();
}

void NPC::SetBattleState(BattleStates battle_state) {
  battle_states_ = battle_state;
}

bool NPC::IsAlive() const {
  return alive_;
}

uint16_t NPC::GetLevel() const {
  return level_;
}

void NPC::AddExperience(std::size_t value) {

}

void NPC::SetLevel(std::uint16_t level) {
  const auto level_before = level_;
  level_ = level;
  character_statistics_list_.OnLevelUpdate(level_ - level_before);
}


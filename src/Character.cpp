#include "Character.hpp"

Character::Character() : uuid_(boost::uuids::random_generator()()) {
}

bool Character::operator==(const Character &character) {
  return uuid_ == character.uuid_;
}

bool Character::operator!=(const Character &character) {
  return !(*this == character);
}

void Character::SetName(const std::string &value) {
  character_name_ = value;
}

void Character::SetId(uint32_t value) {
  id_ = value;
}

void Character::SetAlive(bool value) {
  is_alive_ = value;
}

void Character::SetGender(CharacterGender value) {
  character_gender_ = value;
}

void Character::SetRace(CharacterRace value) {
  character_race_ = value;
}

void Character::SetClass(CharacterClass value) {
  character_class_ = value;
}





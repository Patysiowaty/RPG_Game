#include "Npc.hpp"

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

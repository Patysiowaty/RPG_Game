#include "Character.hpp"

Character::Character() : uuid_(boost::uuids::random_generator()()),
						 character_data_manager_{&character_statistics_, &character_attributes_, &character_level_},
						 item_manager_{&character_inventory_, &character_equipment_, &character_level_, &id_} {
  item_manager_.RegisterHandler(&character_data_manager_);
  character_level_.RegisterHandler(&character_data_manager_);
  character_attributes_.RegisterHandler(&character_data_manager_);
}

bool Character::operator==(const Character &character) {
  return uuid_ == character.uuid_;
}

bool Character::operator!=(const Character &character) {
  return !(*this == character);
}

void Character::SetName(const std::string &name) {
  character_name_ = name;
}

void Character::SetId(uint32_t id) {
  id_ = id;
}





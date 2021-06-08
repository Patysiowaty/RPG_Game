#include "Character.hpp"

Character::Character(std::uint32_t id, std::string character_name) : character_name_{std::move(character_name)},
																	 uuid_(boost::uuids::random_generator()()),
																	 id_{id},
																	 character_data_updater_{&character_statistics_,
																							 &character_attributes_},
																	 item_manager_{
																		 &character_inventory_,
																		 &character_equipment_,
																		 &character_level_, id_} {
  item_manager_.RegisterHandler(&character_data_updater_);
  character_level_.RegisterHandler(&character_data_updater_);
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





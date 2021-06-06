#include "Item.hpp"
Item::Item() {

}

Item::~Item() = default;

bool Item::operator==(const Item &item) {
  return id_ == item.id_;
}

bool Item::operator!=(const Item &item) {
  return !(*this == item);
}

void Item::SetId(uint32_t id) {
  id_ = id;
}

void Item::SetOwnerId(uint32_t owner_id) {
  owner_id_ = owner_id;
}

void Item::SetIsEquipped(bool is_equipped) {
  is_equipped_ = is_equipped;
}

void Item::ChangeItemLocation(ItemLocation item_location) {
  item_location_ = item_location;
}

void Item::SetEquipmentType(ItemType item_type) {
  item_type_ = item_type;
}

void Item::SetName(const std::string &name) {
  name_ = name;
}

void Item::SetDescription(const std::string &description) {
  description_ = description;
}

void Item::SetLevelRequirement(uint16_t level_requirement) {
  level_requirement_ = level_requirement;
}

void Item::SetCharacterClassRequirement(const std::vector<CharacterClass> &character_class_requirement) {
  character_class_requirement_ = character_class_requirement;
}

void Item::SetStrength(int32_t strength) {
  strength_ = strength;
}

void Item::SetDexterity(int32_t dexterity) {
  dexterity_ = dexterity;
}

void Item::SetVitality(int32_t vitality) {
  vitality_ = vitality;
}

void Item::SetIntelligence(int32_t intelligence) {
  intelligence_ = intelligence;
}



#include "Item.hpp"
Item::Item() = default;

Item::Item(std::uint32_t item_id) : id_{item_id} {
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

void Item::SetItemLocation(ItemLocation item_location) {
  location_ = item_location;
}

void Item::SetItemType(ItemType item_type) {
  type_ = item_type;
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

void Item::SetRarity(ItemRarity item_rarity) {
  rarity_ = item_rarity;
}

void Item::SetAttributes(const std::vector<Attribute> &attributes) {
  attributes_ = attributes;
}

void Item::SetIcon(const std::string &icon) {
  icon_ = icon;
}

void Item::SetStatistics(const std::vector<Statistic> &statistics) {
  statistics_ = statistics;
}




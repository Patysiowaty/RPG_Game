#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <memory>
#include "../enums/CharacterClass.hpp"
#include "../enums/ItemType.hpp"
#include "../enums/ItemLocation.hpp"
#include "../enums/ItemRarity.hpp"
#include "../Attribute.hpp"
#include "../enums/AttributeType.hpp"

class Item {
 public:
  Item();
  virtual ~Item();

  bool operator==(const Item &item);
  bool operator!=(const Item &item);

  bool IsEquipped() const { return is_equipped_; }
  ItemType GetItemType() const { return item_type_; }

  ItemLocation GetCurrentLocation() const { return item_location_; }
  uint32_t GetOwnerId() const { return owner_id_; }
  uint16_t GetLevelRequirement() const { return level_requirement_; }
  const std::vector<CharacterClass> &GetClassRequirement() const { return character_class_requirement_; }
  const std::vector<Attribute> &GetAttributes() const { return attributes_; }

  void SetId(uint32_t id);
  void SetOwnerId(uint32_t owner_id);
  void SetIsEquipped(bool is_equipped);
  void SetItemType(ItemType item_type);
  void SetRarity(ItemRarity item_rarity);
  void SetName(const std::string &name);
  void SetDescription(const std::string &description);
  void SetLevelRequirement(uint16_t level_requirement);
  void SetCharacterClassRequirement(const std::vector<CharacterClass> &character_class_requirement);
  void SetAttributes(const std::vector<Attribute> &attributes);
  void SetItemLocation(ItemLocation item_location);

 private:
  uint32_t id_ = 0;
  uint32_t owner_id_ = 0;
  bool is_equipped_ = false;

  ItemType item_type_ = ItemType::kNone;
  ItemLocation item_location_ = ItemLocation::kNone;
  ItemRarity item_rarity_ = ItemRarity::kCommon;

  std::string name_;
  std::string description_;

  uint16_t level_requirement_ = 0;
  std::vector<CharacterClass> character_class_requirement_;

  std::vector<Attribute> attributes_;
};

#endif //ITEM_HPP

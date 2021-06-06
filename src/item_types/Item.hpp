#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <memory>
#include "../enums/CharacterClass.hpp"
#include "../enums/ItemType.hpp"
#include "../enums/ItemLocation.hpp"
#include "../enums/ItemRarity.hpp"

class Item {
 public:
  explicit Item();
  virtual ~Item();

  bool operator==(const Item &item);
  bool operator!=(const Item &item);

  bool IsEquipped() const { return is_equipped_; }
  ItemType GetItemType() const { return item_type_; }
  int32_t GetStrength() const { return strength_; }
  int32_t GetDexterity() const { return dexterity_; }
  int32_t GetVitality() const { return vitality_; }
  int32_t GetIntelligence() const { return intelligence_; }
  ItemLocation GetCurrentLocation() const { return item_location_; }
  uint32_t GetOwnerId() const { return owner_id_; }
  uint16_t GetLevelRequirement() const { return level_requirement_; }
  const std::vector<CharacterClass> &GetClassRequirement() const { return character_class_requirement_; }

  void SetId(uint32_t id);
  void SetOwnerId(uint32_t owner_id);
  void SetIsEquipped(bool is_equipped);
  void SetEquipmentType(ItemType item_type);
  void SetName(const std::string &name);
  void SetDescription(const std::string &description);
  void SetLevelRequirement(uint16_t level_requirement);
  void SetCharacterClassRequirement(const std::vector<CharacterClass> &character_class_requirement);
  void SetStrength(int32_t strength);
  void SetDexterity(int32_t dexterity);
  void SetVitality(int32_t vitality);
  void SetIntelligence(int32_t intelligence);

  void ChangeItemLocation(ItemLocation item_location);

 private:
  uint32_t id_ = 0;
  uint32_t owner_id_ = 0;
  bool is_equipped_ = false;
  ItemType item_type_ = ItemType::kNone;
  ItemLocation item_location_ = ItemLocation::kNone;
  ItemRarity item_rarity_ = ItemRarity::kCommon;

  std::string name_;
  std::string description_;
  std::string template_data_;

  uint16_t level_requirement_ = 0;
  std::vector<CharacterClass> character_class_requirement_;

  int32_t strength_ = 0;
  int32_t dexterity_ = 0;
  int32_t vitality_ = 0;
  int32_t intelligence_ = 0;

};

#endif //ITEM_HPP

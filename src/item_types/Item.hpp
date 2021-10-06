#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <memory>
#include "../enums/CharacterClass.hpp"
#include "../enums/ItemType.hpp"
#include "../enums/ItemLocation.hpp"
#include "../enums/ItemRarity.hpp"
#include "../game_core/Attribute.hpp"
#include "../enums/AttributeType.hpp"
#include "../game_core/Statistic.hpp"

class Item {
 public:
  Item();
  explicit Item(std::uint32_t item_id);
  virtual ~Item();

  bool operator==(const Item &item);
  bool operator!=(const Item &item);

  std::uint32_t GetItemId() const { return id_; }
  std::uint32_t GetOwnerId() const { return owner_id_; }
  bool IsEquipped() const { return is_equipped_; }
  ItemType GetItemType() const { return type_; }
  ItemLocation GetItemLocation() const { return location_; }
  ItemRarity GetItemRarity() const { return rarity_; }
  const std::string &GetItemName() const { return name_; }
  const std::string &GetIconPath() const { return icon_; }
  std::uint16_t GetLevelRequirement() const { return level_requirement_; }
  const std::vector<CharacterClass> &GetClassRequirement() const { return character_class_requirement_; }
  const std::vector<Attribute> &GetAttributes() const { return attributes_; }
  const std::vector<Statistic> &GetStatistics() const { return statistics_; }

  void SetId(std::uint32_t id);
  void SetOwnerId(std::uint32_t owner_id);
  void SetIsEquipped(bool is_equipped);
  void SetItemType(ItemType item_type);
  void SetItemLocation(ItemLocation item_location);
  void SetRarity(ItemRarity item_rarity);
  void SetName(const std::string &name);
  void SetIcon(const std::string &icon);
  void SetDescription(const std::string &description);
  void SetLevelRequirement(uint16_t level_requirement);
  void SetCharacterClassRequirement(const std::vector<CharacterClass> &character_class_requirement);
  void SetAttributes(const std::vector<Attribute> &attributes);
  void SetStatistics(const std::vector<Statistic> &statistics);

 private:
  std::uint32_t id_{0};
  std::uint32_t owner_id_{0};
  bool is_equipped_{false};

  ItemType type_ = ItemType::kNone;
  ItemLocation location_ = ItemLocation::kNone;
  ItemRarity rarity_ = ItemRarity::kCommon;

  std::string name_;
  std::string description_;
  std::string icon_;
  std::uint32_t price_{0};

  std::uint16_t level_requirement_{0};
  std::vector<CharacterClass> character_class_requirement_;

  std::vector<Attribute> attributes_;
  std::vector<Statistic> statistics_;
};

#endif //ITEM_HPP

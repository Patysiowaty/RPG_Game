#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "enums/CharacterGender.hpp"
#include "enums/CharacterRace.hpp"
#include "enums/CharacterClass.hpp"
#include "item_types/Item.hpp"
#include "CharacterInventory.hpp"
#include "CharacterEquipment.hpp"
#include "CharacterAttributes.hpp"
#include "CharacterLevel.hpp"
#include "CharacterStatistics.hpp"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include "ItemManager.hpp"
#include "LevelManager.hpp"

class Character {
 public:
  Character(std::uint32_t id, std::string character_name);
  virtual ~Character() = default;

  bool operator==(const Character &character);
  bool operator!=(const Character &character);

  void SetName(const std::string &name);
  void SetId(uint32_t id);

  const std::string &GetCharacterName() const { return character_name_; }
  std::uint32_t GetCharacterId() const { return id_; }
  CharacterClass GetCharacterClass() const { return character_class_; }

  ItemManager &GetItemManager() { return item_manager_; }
  LevelManager &GetLevelManager() { return level_manager_; }

  virtual void OnAttributesUpdate() = 0;
  virtual void OnStatisticsUpdate() = 0;

  virtual void OnBattleEnd(bool winner) = 0;
  virtual void Attack() = 0;
  virtual void MoveCharacter() = 0;

 private:
  std::uint32_t id_ = 0;
  boost::uuids::uuid uuid_;
  std::string character_name_;

  CharacterGender character_gender_ = CharacterGender::kNone;
  CharacterRace character_race_ = CharacterRace::kNone;
  CharacterClass character_class_ = CharacterClass::kNone;

  CharacterAttributes character_attributes_;
  CharacterStatistics character_statistics_;
  CharacterEquipment character_equipment_;
  CharacterInventory character_inventory_;
  CharacterLevel character_level_;
  ItemManager item_manager_;
  LevelManager level_manager_;
};

#endif //CHARACTER_HPP
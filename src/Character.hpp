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
#include "CharacterDataManager.hpp"

class Character {
 public:
  Character();
  virtual ~Character() = default;

  bool operator==(const Character &character);
  bool operator!=(const Character &character);

  void SetName(const std::string &name);
  void SetId(uint32_t id);

  const std::string &GetName() const { return character_name_; }
  std::uint32_t GetId() const { return id_; }
  boost::uuids::uuid GetUuid() const { return uuid_; }
  CharacterClass GetClass() const { return character_class_; }
  CharacterGender GetGender() const { return character_gender_; }
  CharacterRace GetRace() const { return character_race_; }

  ItemManager &GetItemManager() { return item_manager_; }
  CharacterDataManager &GetCharacterDataManager() { return character_data_manager_; }

  virtual void Attack() = 0;
  virtual void MoveCharacter() = 0;

 protected:
  CharacterAttributes &GetAttributes() { return character_attributes_; }
  CharacterStatistics &GetStatistics() { return character_statistics_; }
  CharacterLevel &GetLevel() { return character_level_; }

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
  CharacterDataManager character_data_manager_;
};

#endif //CHARACTER_HPP
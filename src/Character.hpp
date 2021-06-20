#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "enums/CharacterGender.hpp"
#include "enums/CharacterRace.hpp"
#include "enums/CharacterClass.hpp"
#include "item_types/Item.hpp"
#include "PlayerInventory.hpp"
#include "PlayerEquipment.hpp"
#include "PlayerAttributes.hpp"
#include "PlayerLevel.hpp"
#include "PlayerStatistics.hpp"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include "ItemsInteractor.hpp"


class Character {
 public:
  explicit Character();
  virtual ~Character() = default;

  bool operator==(const Character &character);
  bool operator!=(const Character &character);

  void SetName(const std::string &value);
  void SetId(uint32_t value);
  void SetAlive(bool value);
  void SetGender(CharacterGender value);
  void SetRace(CharacterRace value);
  void SetClass(CharacterClass value);

  const std::string &GetName() const { return character_name_; }
  std::uint32_t *GetId() { return &id_; }
  bool isAlive() const { return is_alive_; };
  boost::uuids::uuid GetUuid() const { return uuid_; }
  CharacterClass GetClass() const { return character_class_; }
  CharacterGender GetGender() const { return character_gender_; }
  CharacterRace GetRace() const { return character_race_; }

  virtual void Attack() = 0;
  virtual void MoveCharacter() = 0;

 private:
  std::uint32_t id_;
  boost::uuids::uuid uuid_;
  std::string character_name_;
  bool is_alive_{true};

  CharacterGender character_gender_ = CharacterGender::kNone;
  CharacterRace character_race_ = CharacterRace::kNone;
  CharacterClass character_class_ = CharacterClass::kNone;
};

#endif //CHARACTER_HPP
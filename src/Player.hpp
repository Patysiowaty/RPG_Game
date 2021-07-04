#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "interfaces/ICharacter.hpp"
#include "item_types/SwordItem.hpp"
#include "item_types/ConsumptiveItem.hpp"
#include "interfaces/IjsonSerializable.hpp"
#include "ItemsInteractor.hpp"
#include "PlayerLevel.hpp"
#include "PlayerAttributes.hpp"
#include "PlayerStatistics.hpp"
#include "PlayerEquipment.hpp"
#include "PlayerInventory.hpp"

class Player : public ICharacter, public IJSONSerializable {
 public:
  Player();

  void SetName(const std::string &value) override;
  void SetId(uint32_t value) override;
  void SetGender(CharacterGender value) override;
  void SetRace(CharacterRace value) override;
  void SetClass(CharacterClass value) override;
  void SetAlive(bool value) override;
  const std::string &GetName() const override;
  uint32_t GetId() const override;
  bool IsAlive() const override;
  boost::uuids::uuid GetUuid() const override;
  CharacterClass GetClass() const override;
  CharacterGender GetGender() const override;
  CharacterRace GetRace() const override;

  boost::property_tree::ptree Serialize() override;
  void Deserialize(const boost::property_tree::ptree &ptree) override;
  void Attack() override;

  ItemsInteractor &GetItemsInteractor() { return items_interactor_; }
  PlayerLevel &GetLevel() { return player_level_; }

 private:
  std::uint32_t id_;
  boost::uuids::uuid uuid_;
  std::string name_;
  bool is_alive_{true};

  CharacterGender gender_ = CharacterGender::kNone;
  CharacterRace race_ = CharacterRace::kNone;
  CharacterClass class_ = CharacterClass::kNone;

  PlayerAttributes player_attributes_;
  PlayerStatistics player_statistics_;
  PlayerEquipment player_equipment_;
  PlayerInventory player_inventory_;
  PlayerLevel player_level_;
  ItemsInteractor items_interactor_;
};

#endif //PLAYER_HPP

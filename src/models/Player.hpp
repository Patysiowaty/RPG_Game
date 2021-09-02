#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics/Transformable.hpp>
#include "../interfaces/ICharacter.hpp"
#include "../item_types/SwordItem.hpp"
#include "../item_types/ConsumptiveItem.hpp"
#include "../interfaces/IjsonSerializable.hpp"
#include "../game_core/ItemsInteractor.hpp"
#include "../game_core/PlayerLevel.hpp"
#include "../game_core/PlayerAttributes.hpp"
#include "../game_core/CharacterStatisticsList.hpp"
#include "../game_core/PlayerEquipment.hpp"
#include "../game_core/PlayerInventory.hpp"
#include "../interfaces/IFightable.hpp"
#include "../interfaces/IWalkable.hpp"

class Player
	: public ICharacter, public IJSONSerializable, public IJSONDeserializable, public IFightable,
		public sf::Transformable {
 public:
  Player();

  void SetName(const std::string &value) override;
  void SetId(uint32_t value) override;
  void SetGender(CharacterGender value) override;
  void SetRace(CharacterRace value) override;
  void SetClass(CharacterClass value) override;
  const std::string &GetName() const override;
  uint32_t GetId() const override;
  boost::uuids::uuid GetUuid() const override;
  CharacterClass GetClass() const override;
  CharacterGender GetGender() const override;
  CharacterRace GetRace() const override;

  void Update(float delta_time);

  const PlayerInventory &GetPlayerInventory() const { return player_inventory_; }

  boost::property_tree::ptree Serialize() const override;
  void Deserialize(const boost::property_tree::ptree &ptree) override;

  std::int32_t Attack() const override;
  void TakeDamage(std::int32_t value) override;
  std::int32_t GetCurrentHealth() const override;
  void SetBattleState(BattleStates battle_state) override;
  bool IsAlive() const override;
  std::uint16_t GetLevel() const override;
  void AddExperience(std::size_t value) override;

 private:
  std::uint32_t id_;
  boost::uuids::uuid uuid_;
  std::string name_;
  bool is_alive_{true};
  BattleStates battle_state_{BattleStates::kNone};

  CharacterGender gender_{CharacterGender::kNone};
  CharacterRace race_{CharacterRace::kNone};
  CharacterClass class_{CharacterClass::kNone};

  PlayerAttributes player_attributes_;
  CharacterStatisticsList player_statistics_;
  PlayerEquipment player_equipment_;
  PlayerInventory player_inventory_;
  PlayerLevel player_level_;
  ItemsInteractor items_interactor_;
};

#endif //PLAYER_HPP

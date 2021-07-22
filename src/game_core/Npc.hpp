#ifndef NPC_HPP
#define NPC_HPP

#include "../interfaces/ICharacter.hpp"
#include "../interfaces/IFightable.hpp"
#include "CharacterStatisticsList.hpp"
class NPC : public ICharacter, public IFightable {
 public:
  NPC();
  int32_t Attack() const override;
  void TakeDamage(std::int32_t value) override;
  int32_t GetCurrentHealth() const override;
  void SetBattleState(BattleStates battle_state) override;
  bool IsAlive() const override;
  uint16_t GetLevel() const override;
  void AddExperience(std::size_t value) override;

  void SetName(const std::string &value) override;
  void SetId(uint32_t value) override;
  void SetGender(CharacterGender value) override;
  void SetRace(CharacterRace value) override;
  void SetClass(CharacterClass value) override;

  void SetLevel(std::uint16_t level);

  const std::string &GetName() const override;
  uint32_t GetId() const override;

  boost::uuids::uuid GetUuid() const override;
  CharacterClass GetClass() const override;
  CharacterGender GetGender() const override;
  CharacterRace GetRace() const override;

 private:
  std::uint32_t id_;
  boost::uuids::uuid uuid_;
  std::string name_;
  CharacterRace race_;
  CharacterGender gender_;
  CharacterClass class_;
  BattleStates battle_states_;

  std::uint16_t level_;

  CharacterStatisticsList character_statistics_list_;

  bool alive_{true};
};
#endif //NPC_HPP

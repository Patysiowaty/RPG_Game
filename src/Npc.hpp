#ifndef NPC_HPP
#define NPC_HPP

#include "interfaces/ICharacter.hpp"
class NPC : public ICharacter {
 public:
  NPC();

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


 private:
  std::uint32_t id_;
  boost::uuids::uuid uuid_;
  std::string name_;
  CharacterRace race_;
  CharacterGender gender_;
  CharacterClass class_;

  bool alive_{true};
};
#endif //NPC_HPP

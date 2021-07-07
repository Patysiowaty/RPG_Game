#ifndef ICHARACTER_HPP
#define ICHARACTER_HPP
#include "../enums/CharacterGender.hpp"
#include "../enums/CharacterRace.hpp"
#include "../enums/CharacterClass.hpp"
#include <boost/uuid/uuid.hpp>
#include <string>

class ICharacter {
 public:
  virtual ~ICharacter() = default;

  virtual void SetName(const std::string &value) = 0;
  virtual void SetId(uint32_t value) = 0;
  virtual void SetGender(CharacterGender value) = 0;
  virtual void SetRace(CharacterRace value) = 0;
  virtual void SetClass(CharacterClass value) = 0;

  virtual const std::string &GetName() const = 0;
  virtual std::uint32_t GetId() const = 0;
  virtual boost::uuids::uuid GetUuid() const = 0;
  virtual CharacterClass GetClass() const = 0;
  virtual CharacterGender GetGender() const = 0;
  virtual CharacterRace GetRace() const = 0;
};

#endif //ICHARACTER_HPP
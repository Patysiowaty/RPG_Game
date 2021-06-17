#ifndef ICHARACTERBUILDER_HPP
#define ICHARACTERBUILDER_HPP
#include <memory>
#include "../Character.hpp"

class ICharacterBuilder {
 public:
  std::shared_ptr<Character> MakeCharacter() = 0;
  bool BuildBasicData() = 0;
  bool BuildAttributes() = 0;
  bool BuildStatistics() = 0;
  bool BuildInventory() = 0;
  bool BuildEquipment() = 0;
};

#endif //ICHARACTERBUILDER_HPP

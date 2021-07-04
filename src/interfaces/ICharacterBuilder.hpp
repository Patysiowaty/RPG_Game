#ifndef ICHARACTERBUILDER_HPP
#define ICHARACTERBUILDER_HPP
#include <memory>
#include "ICharacter.hpp"

class ICharacterBuilder {
 public:
  std::shared_ptr<ICharacter> MakeCharacter() = 0;
};

#endif //ICHARACTERBUILDER_HPP

#ifndef CHARACTERCLASS_HPP
#define CHARACTERCLASS_HPP
#include <cstdint>

enum class CharacterClass : std::uint16_t {
  kNone = 1 << 0,
  kWarrior = 1 << 1,
  kMage = 1 << 2,
  kHunter = 1 << 3,
};

#endif //CHARACTERCLASS_HPP

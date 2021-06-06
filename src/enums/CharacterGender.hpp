#ifndef CHARACTERGENDER_HPP
#define CHARACTERGENDER_HPP

#include <cstdint>

enum class CharacterGender : uint16_t {
  kNone = 1 << 0,
  kMale = 1 << 1,
  kFemale = 1 << 2
};

#endif //CHARACTERGENDER_HPP

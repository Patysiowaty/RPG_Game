#ifndef ITEMTYPE_HPP
#define ITEMTYPE_HPP
#include <cstdint>

enum class ItemType : uint16_t {
  kNone = 0,
  kHelmet = 1,
  kRing = 2,
  kNecklace = 3,
  kGloves = 4,
  kOneHandedSword = 5,
  kArmor = 6,
  kOffHand = 7,
  kPants = 8,
  kBoots = 9,
  kConsumptive = 10
};

#endif //ITEMTYPE_HPP

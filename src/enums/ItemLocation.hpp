#ifndef ITEMLOCATION_HPP
#define ITEMLOCATION_HPP
#include <cstdint>
enum class ItemLocation : uint32_t {
  kNone = 1 << 0,
  kCharacterInventory = 1 << 1,
  kCharacterEquipment = 1 << 2,
  kCharacterDeposit = 1 << 3
};

#endif //ITEMLOCATION_HPP

#ifndef ITEMLOCATION_HPP
#define ITEMLOCATION_HPP
#include <cstdint>
enum class ItemLocation : uint32_t {
  kNone = 0,
  kCharacterInventory,
  kCharacterEquipment,
  kCharacterDeposit
};

#endif //ITEMLOCATION_HPP

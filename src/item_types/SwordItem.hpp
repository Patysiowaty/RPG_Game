#ifndef SWORDITEM_HPP
#define SWORDITEM_HPP
#include "Item.hpp"

class SwordItem : public Item {
 public:
  SwordItem();

  void SetAttackValue(std::int32_t value);
  int32_t GetAttackValue() const;

 private:
  std::unique_ptr<std::int32_t> attack_value_;
};

#endif //SWORDITEM_HPP

#include "SwordItem.hpp"
SwordItem::SwordItem() {

}

void SwordItem::SetAttackValue(std::int32_t value) {
  attack_value_ = std::make_unique<std::int32_t>(value);
}

int32_t SwordItem::GetAttackValue() const {
  return attack_value_ ? *attack_value_ : 0;
}


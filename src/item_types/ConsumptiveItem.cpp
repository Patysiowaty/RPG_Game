#include "ConsumptiveItem.hpp"
ConsumptiveItem::ConsumptiveItem() = default;

ConsumptiveItem::ConsumptiveItem(std::uint32_t item_id) : Item(item_id) {
}

ConsumptionEffect ConsumptiveItem::GetAfterConsumptionEffect() {
}









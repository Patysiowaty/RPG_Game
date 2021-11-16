#include "KeyItem.hpp"
KeyItem::KeyItem() = default;

KeyItem::KeyItem(std::uint32_t item_id) : Item(item_id) {

}

void KeyItem::SetQuestBelonging(std::int32_t quest_id) {
  quest_id_belonging_ = quest_id;
}


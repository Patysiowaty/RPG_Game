#ifndef KEYITEM_HPP
#define KEYITEM_HPP

#include "Item.hpp"
class KeyItem : public Item {
 public:
  KeyItem();
  explicit KeyItem(std::uint32_t item_id);
  void SetQuestBelonging(std::int32_t quest_id);

 private:
  std::int32_t quest_id_belonging_{-1};
};

#endif //KEYITEM_HPP

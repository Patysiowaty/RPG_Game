#ifndef SLOTINDEX_HPP
#define SLOTINDEX_HPP

struct SlotIndex {
  const int first;
  const int second;
  bool operator<(const SlotIndex &slot_index) const {
	return (first < slot_index.first) || (first == slot_index.first && second < slot_index.second);
  }
};
#endif //SLOTINDEX_HPP

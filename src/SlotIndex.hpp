#ifndef SLOTINDEX_HPP
#define SLOTINDEX_HPP

struct SlotIndex {
  bool operator<(const SlotIndex &rhs) const {
	return std::make_tuple(z, y, x) < std::make_tuple(rhs.z, rhs.y, rhs.x);
  }

  bool operator>(const SlotIndex &rhs) const {
	return rhs < *this;
  }

  bool operator==(const SlotIndex &rhs) const {
	return z == rhs.z && x == rhs.x && y == rhs.y;
  }

  bool operator!=(const SlotIndex &rhs) const {
	return !(*this == rhs);
  }

  const int x;
  const int y;
  const int z{0};
};

#endif //SLOTINDEX_HPP

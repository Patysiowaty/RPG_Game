#ifndef IWALKABLE_HPP
#define IWALKABLE_HPP
#include <cstdint>

class IWalkable {
 public:
  virtual ~IWalkable() = default;
  using CharacterPosition = std::pair<size_t, size_t>;

  virtual void SetPosition(std::uint32_t x, std::uint32_t y) = 0;
  virtual void SetPosition(const CharacterPosition &position) = 0;

  virtual const CharacterPosition &GetPosition() const = 0;
};

#endif //IWALKABLE_HPP

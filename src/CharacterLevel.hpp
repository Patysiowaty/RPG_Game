#ifndef CHARACTERLEVEL_HPP
#define CHARACTERLEVEL_HPP

#include <memory>

class CharacterLevel {
 public:
  explicit CharacterLevel(std::uint16_t level = 0);

  bool LevelUp();

  void SetLevel(std::uint16_t value);
  std::uint16_t GetLevel() const { return level_; }
  bool HasMaximumLevel() const;

 private:
  static constexpr std::uint16_t level_cap_ = 50;
  std::uint16_t level_ = 0;
};

#endif //CHARACTERLEVEL_HPP

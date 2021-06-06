#ifndef PLAYEREXPERIENCE_HPP
#define PLAYEREXPERIENCE_HPP

#include <memory>

class PlayerExperience {
 public:
  explicit PlayerExperience(size_t total_experience = 0, size_t next_level_experience = 0);
  ~PlayerExperience();

  void AddExperience(int32_t value);
  void CalculateNextLevelExperience(std::uint16_t value);
  bool ShouldLevelUp() const;
  void ShrinkToFit();
  double GetNextLevelPercentProgress() const;

 private:
  bool IsValidExperience(int32_t value) const;

 private:
  size_t total_experience_;
  size_t next_level_experience_;
};

#endif //PLAYEREXPERIENCE_HPP

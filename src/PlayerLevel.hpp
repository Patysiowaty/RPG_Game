#ifndef PLAYERLEVEL_HPP
#define PLAYERLEVEL_HPP

#include <memory>
#include <cstdint>
#include <vector>
#include "interfaces/ILevelHandler.hpp"
#include "interfaces/IPublisher.hpp"

class PlayerLevel : public IPublisher<ILevelHandler> {
 public:
  explicit PlayerLevel(std::uint16_t level = 1, std::size_t total_exp = 0);

  void AddExperience(int32_t value);
  void RegisterHandler(ILevelHandler *level_handler) override;

  void SetExperience(std::size_t value);
  void SetLevel(std::uint16_t value);

  std::uint16_t GetLevel() const;
  std::pair<size_t, size_t> GetExperience() const;
  double GetExperiencePercent() const;

  bool HasMaximumLevel() const;

 private:
  size_t CalculateNextLevelExperience();
  size_t CalculateNextLevelExperience(std::uint16_t);
  bool LevelUp();

 private:
  static constexpr std::uint16_t kLevelCap{50};
  std::uint16_t level_{1};

  std::size_t total_experience_{0};
  std::size_t next_level_experience_{0};

  std::vector<ILevelHandler *> handlers_;
};

#endif //PLAYERLEVEL_HPP

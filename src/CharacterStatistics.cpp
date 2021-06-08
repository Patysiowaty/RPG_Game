#include "CharacterStatistics.hpp"
CharacterStatistics::CharacterStatistics() {
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kAttack));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kMagicAttack));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kHealth));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kStamina));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kMana));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kArmor));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kCriticalStrikeRatio));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kCriticalStrikeForce));
  statistic_.emplace_back(std::make_shared<Statistic>(StatisticType::kEvadeRatio));
}

std::shared_ptr<Statistic> CharacterStatistics::GetStatistic(StatisticType statistic_type) const {
  const auto
	  it = std::find_if(statistic_.cbegin(), statistic_.cend(),
						[=](const std::shared_ptr<Statistic> &statistic) {
						  return statistic->GetType() == statistic_type;
						});

  return it != statistic_.cend() ? *it : nullptr;
}


















#include "CharacterStatistics.hpp"
CharacterStatistics::CharacterStatistics() {
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kAttack));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kMagicAttack));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kHealth));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kStamina));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kMana));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kArmor));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kCriticalStrikeRatio));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kCriticalStrikeForce));
  statistics_.emplace_back(std::make_shared<Statistic>(StatisticType::kEvadeRatio));
}

std::shared_ptr<Statistic> CharacterStatistics::GetStatistic(StatisticType statistic_type) const {
  const auto it = std::find_if(statistics_.cbegin(), statistics_.cend(),
							   [=](const std::shared_ptr<Statistic> &statistic) {
								 return statistic->GetType() == statistic_type;
							   });

  return it != statistics_.cend() ? *it : nullptr;
}

void CharacterStatistics::AddStatistic(StatisticType statistic_type, std::int32_t value) {
  if (GetStatistic(statistic_type))
	throw std::invalid_argument{"CharacterStatistics::AddStatistic -> statistic already exist"};

  statistics_.emplace_back(std::make_shared<Statistic>(statistic_type, value));
}

void CharacterStatistics::AddStatistic(std::shared_ptr<Statistic> statistic) {
  if (GetStatistic(statistic->GetType()))
	throw std::invalid_argument{"CharacterStatistics::AddStatistic -> statistic already exist"};

  statistics_.push_back(std::move(statistic));
}


















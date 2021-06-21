#include "PlayerStatistics.hpp"
PlayerStatistics::PlayerStatistics() {
  single_statistics_.emplace_back(std::make_unique<SingleStatistic>(StatisticType::kAttack, 0));
  single_statistics_.emplace_back(std::make_unique<SingleStatistic>(StatisticType::kMagicAttack));
  single_statistics_.emplace_back(std::make_unique<SingleStatistic>(StatisticType::kArmor));
  single_statistics_.emplace_back(std::make_unique<SingleStatistic>(StatisticType::kCriticalStrikeRatio));
  single_statistics_.emplace_back(std::make_unique<SingleStatistic>(StatisticType::kCriticalStrikeForce));
  single_statistics_.emplace_back(std::make_unique<SingleStatistic>(StatisticType::kEvadeRatio));
  range_statistics_.emplace_back(std::make_unique<RangeStatistic>(StatisticType::kHealth));
  range_statistics_.emplace_back(std::make_unique<RangeStatistic>(StatisticType::kStamina));
  range_statistics_.emplace_back(std::make_unique<RangeStatistic>(StatisticType::kMana));
}

const std::unique_ptr<SingleStatistic> &PlayerStatistics::GetSingleStatistic(StatisticType statistic_type) const {
  auto it = std::find_if(single_statistics_.begin(), single_statistics_.end(),
						 [=](const std::unique_ptr<SingleStatistic> &statistic) {
						   return statistic->GetType() == statistic_type;
						 });

  if (it != single_statistics_.end())
	throw std::invalid_argument{"layerStatistics::GetSingleStatistic -> invalid statistic type."};

  return *it;
}

const std::unique_ptr<RangeStatistic> &PlayerStatistics::GetRangeStatistic(StatisticType statistic_type) const {
  auto it = std::find_if(range_statistics_.begin(), range_statistics_.end(),
						 [=](const std::unique_ptr<RangeStatistic> &statistic) {
						   return statistic->GetType() == statistic_type;
						 });

  if (it != range_statistics_.end())
	throw std::invalid_argument{"layerStatistics::GetRangeStatistic -> invalid statistic type."};

  return *it;
}

void PlayerStatistics::AddSingleStatistic(StatisticType statistic_type, std::int32_t value) {
  if (GetSingleStatistic(statistic_type))
	throw std::invalid_argument{"PlayerStatistics::AddSingleStatistic -> statistic already exist"};

  single_statistics_.emplace_back(std::make_unique<SingleStatistic>(statistic_type, value));
}

void PlayerStatistics::AddRangeStatistic(StatisticType statistic_type, std::int32_t value) {
  if (GetRangeStatistic(statistic_type))
	throw std::invalid_argument{"PlayerStatistics::AddRangeStatistic -> statistic already exist"};

  range_statistics_.emplace_back(std::make_unique<RangeStatistic>(statistic_type, value));
}

void PlayerStatistics::OnAttributesUpdate(const std::vector<std::unique_ptr<Attribute>> &attributes) {
  for (const auto &attribute: attributes)
	ReloadStatistics(attribute);
}

void PlayerStatistics::OnAttributeUpdate(const std::unique_ptr<Attribute> &attribute) {
  ReloadStatistics(attribute);
}

void PlayerStatistics::OnLevelRaise() {
  player_level_++;

  const auto &health = GetRangeStatistic(StatisticType::kHealth);
  health->SetValue(health->GetMaxValue());

  const auto &stamina = GetRangeStatistic(StatisticType::kStamina);
  stamina->SetValue(stamina->GetMaxValue());

  const auto &mana = GetRangeStatistic(StatisticType::kMana);
  mana->SetValue(mana->GetMaxValue());
}

void PlayerStatistics::OnLevelDowngrade() {
  player_level_--;

}

void PlayerStatistics::OnLevelUpdate(int value) {
  player_level_ += value;

}

void PlayerStatistics::ReloadStatistics(const std::unique_ptr<Attribute> &attribute) {
  switch (attribute->GetType()) {
	case AttributeType::kStrength:
	  break;
	case AttributeType::kDexterity:
	  break;
	case AttributeType::kVitality:
	  break;
	case AttributeType::kIntelligence:
	  break;
	default:
	  throw std::logic_error{"PlayerStatistics::ReloadStatistics - unknown attribute!"};
  }
}

void PlayerStatistics::OnEquipItem(const std::shared_ptr<Item> &item) {

}

void PlayerStatistics::OnTakeOffItem(const std::shared_ptr<Item> &item) {

}

void PlayerStatistics::OnUsedItem(const std::shared_ptr<IConsumable> &item) {
  const auto &effect = item->GetAfterConsumptionEffect().GetStatisticsEffect();

  for (const auto&[type, value]: effect)
	GetRangeStatistic(type)->AddValue(value);
}



















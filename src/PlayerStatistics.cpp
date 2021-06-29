#include "PlayerStatistics.hpp"
#include <iostream>
PlayerStatistics::PlayerStatistics() {
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kAttack, 0));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kMagicAttack, 0));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kArmor, 0));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kCriticalStrikeRatio, 0));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kCriticalStrikeForce, 1));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kEvadeRatio, 0));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kHealth, 100, 100));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kStamina, 100, 100));
  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(StatisticType::kMana, 100, 100));
}

const StatisticPtr &PlayerStatistics::GetStatistic(StatisticType statistic_type) const {
  auto it = std::find_if(statistic_list_.begin(), statistic_list_.end(),
						 [=](const std::unique_ptr<SinglePlayerStatistic> &statistic) {
						   return statistic->GetType() == statistic_type;
						 });

  if (it != statistic_list_.end())
	throw std::invalid_argument{"layerStatistics::GetRangeStatistic -> invalid statistic type."};

  return *it;
}

void PlayerStatistics::AddNewStatistic(StatisticType statistic_type, std::int32_t max_value, std::int32_t value) {
  if (GetStatistic(statistic_type))
	throw std::invalid_argument{"PlayerStatistics::AddRangeStatistic -> statistic already exist"};

  statistic_list_.emplace_back(std::make_unique<SinglePlayerStatistic>(statistic_type, max_value, value));
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

  const auto &health = GetStatistic(StatisticType::kHealth);
  health->SetValue(health->GetMaxValue());

  const auto &stamina = GetStatistic(StatisticType::kStamina);
  stamina->SetValue(stamina->GetMaxValue());

  const auto &mana = GetStatistic(StatisticType::kMana);
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

  for (const auto&[type, value]: effect) {
	try {
	  GetStatistic(type)->AddValue(value);
	} catch (std::invalid_argument &e) {
	  std::cerr << e.what();
	  continue;
	}
  }
}



















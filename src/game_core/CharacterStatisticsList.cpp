#include "CharacterStatisticsList.hpp"
#include <iostream>
CharacterStatisticsList::CharacterStatisticsList() = default;

const StatisticPtr &CharacterStatisticsList::GetStatistic(StatisticType statistic_type) const {
  if (statistics_list_.empty())
	throw std::invalid_argument{"CharacterStatisticsList::GetStatistic -> empty statistic list."};

  auto it = std::find_if(statistics_list_.begin(), statistics_list_.end(),
						 [=](const std::unique_ptr<CharacterStatistic> &statistic) {
						   return statistic->GetType() == statistic_type;
						 });

  if (it == statistics_list_.end())
	throw std::invalid_argument{"CharacterStatisticsList::GetStatistic -> invalid statistic type."};

  return *it;
}

void CharacterStatisticsList::AddStatistic(StatisticType statistic_type, std::int32_t max_value, std::int32_t value) {

  auto it = std::find_if(statistics_list_.begin(), statistics_list_.end(),
						 [=](const std::unique_ptr<CharacterStatistic> &statistic) {
						   return statistic->GetType() == statistic_type;
						 });

  if (it != statistics_list_.end())
	throw std::invalid_argument{"CharacterStatisticsList::AddRangeStatistic -> statistic already exist"};

  statistics_list_.emplace_back(std::make_unique<CharacterStatistic>(statistic_type, max_value, value));
}

void CharacterStatisticsList::OnAttributesUpdate(const std::vector<std::unique_ptr<Attribute>> &attributes) {
  for (const auto &attribute: attributes)
	ReloadStatistics(attribute);
}

void CharacterStatisticsList::OnAttributeUpdate(const std::unique_ptr<Attribute> &attribute) {
  ReloadStatistics(attribute);
}

void CharacterStatisticsList::OnLevelRaise() {
  player_level_++;

  const auto &health = GetStatistic(StatisticType::kHealth);
  health->SetValue(health->GetMaxValue());

  const auto &stamina = GetStatistic(StatisticType::kStamina);
  stamina->SetValue(stamina->GetMaxValue());

  const auto &mana = GetStatistic(StatisticType::kMana);
  mana->SetValue(mana->GetMaxValue());
}

void CharacterStatisticsList::OnLevelDowngrade() {
  player_level_--;

}

void CharacterStatisticsList::OnLevelUpdate(int value) {
  player_level_ += value;

}

void CharacterStatisticsList::ReloadStatistics(const std::unique_ptr<Attribute> &attribute) {
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
	  throw std::logic_error{"CharacterStatisticsList::ReloadStatistics - unknown attribute!"};
  }
}

void CharacterStatisticsList::OnEquipItem(const std::shared_ptr<Item> &item) {
  const auto &kStatsList = item->GetStatistics();
  if (kStatsList.empty()) return;

  for (const auto &stat: kStatsList) {
	const auto kType = stat.GetType();
	const auto kValue = stat.GetValue();
	GetStatistic(kType)->AddMaxValue(kValue);
  }
}

void CharacterStatisticsList::OnTakeOffItem(const std::shared_ptr<Item> &item) {
  const auto &kStatsList = item->GetStatistics();
  if (kStatsList.empty()) return;

  for (const auto &stat: kStatsList) {
	const auto kType = stat.GetType();
	const auto kValue = stat.GetValue();
	GetStatistic(kType)->SubtractMaxValue(kValue);
  }
}

void CharacterStatisticsList::OnUsedItem(const std::shared_ptr<IConsumable> &item) {
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



















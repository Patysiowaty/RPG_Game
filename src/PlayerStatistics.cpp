#include "PlayerStatistics.hpp"
PlayerStatistics::PlayerStatistics() {
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

std::shared_ptr<Statistic> PlayerStatistics::GetStatistic(StatisticType statistic_type) const {
  const auto it = std::find_if(statistics_.cbegin(), statistics_.cend(),
							   [=](const std::shared_ptr<Statistic> &statistic) {
								 return statistic->GetType() == statistic_type;
							   });

  return it != statistics_.cend() ? *it : nullptr;
}

void PlayerStatistics::AddStatistic(StatisticType statistic_type, std::int32_t value) {
  if (GetStatistic(statistic_type))
	throw std::invalid_argument{"PlayerStatistics::AddStatistic -> statistic already exist"};

  statistics_.emplace_back(std::make_shared<Statistic>(statistic_type, value));
}

void PlayerStatistics::AddStatistic(std::shared_ptr<Statistic> statistic) {
  if (GetStatistic(statistic->GetType()))
	throw std::invalid_argument{"PlayerStatistics::AddStatistic -> statistic already exist"};

  statistics_.push_back(std::move(statistic));
}

void PlayerStatistics::OnAttributesUpdate(const std::vector<std::shared_ptr<Attribute>> &attributes) {
  for (const auto &attribute: attributes)
	ReloadStatistics(attribute);
}

void PlayerStatistics::OnAttributeUpdate(const std::shared_ptr<Attribute> &attribute) {
  ReloadStatistics(attribute);
}

void PlayerStatistics::OnLevelRaise() {
  player_level_++;

  auto health = GetStatistic(StatisticType::kHealth);
  health->SetValue(health->GetMaxValue());

  auto stamina = GetStatistic(StatisticType::kStamina);
  stamina->SetValue(stamina->GetMaxValue());

  auto mana = GetStatistic(StatisticType::kMana);
  mana->SetValue(mana->GetMaxValue());
}

void PlayerStatistics::OnLevelDowngrade() {
  player_level_--;

}

void PlayerStatistics::OnLevelUpdate(int value) {
  player_level_ += value;

}

void PlayerStatistics::ReloadStatistics(const std::shared_ptr<Attribute> &attribute) {
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
void PlayerStatistics::OnUsedItem(const std::shared_ptr<Item> &item) {

}
















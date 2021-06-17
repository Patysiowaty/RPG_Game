#include "Player.hpp"

#include <boost/uuid/uuid_io.hpp>

Player::Player() {

}

void Player::Attack() {

}

void Player::MoveCharacter() {

}

boost::property_tree::ptree Player::Serialize() {
  boost::property_tree::ptree ptree;

  ptree.put("id", GetId());
  ptree.put("uuid", boost::uuids::to_string(GetUuid()));
  ptree.put("name", GetName());
  ptree.put("gender", static_cast<int>(GetGender()));
  ptree.put("race", static_cast<int>(GetRace()));
  ptree.put("class", static_cast<int>(GetClass()));
  ptree.put("level", GetLevel().GetLevel());
  ptree.put("experience", GetLevel().GetExperience().first);

  ptree.put("attributes.strength", GetAttributes().GetAttribute(AttributeType::kStrength)->GetValue());
  ptree.add("attributes.dexterity", GetAttributes().GetAttribute(AttributeType::kDexterity)->GetValue());
  ptree.add("attributes.vitality", GetAttributes().GetAttribute(AttributeType::kVitality)->GetValue());
  ptree.add("attributes.intelligence", GetAttributes().GetAttribute(AttributeType::kIntelligence)->GetValue());

  ptree.put("statistics.attack", GetStatistics().GetStatistic(StatisticType::kAttack)->GetValue());
  ptree.add("statistics.attackMax", GetStatistics().GetStatistic(StatisticType::kAttack)->GetMaxValue());
  ptree.add("statistics.health", GetStatistics().GetStatistic(StatisticType::kHealth)->GetValue());
  ptree.add("statistics.healthMax", GetStatistics().GetStatistic(StatisticType::kHealth)->GetMaxValue());
  ptree.add("statistics.stamina", GetStatistics().GetStatistic(StatisticType::kStamina)->GetValue());
  ptree.add("statistics.staminaMax", GetStatistics().GetStatistic(StatisticType::kStamina)->GetMaxValue());
  ptree.add("statistics.mana", GetStatistics().GetStatistic(StatisticType::kMana)->GetValue());
  ptree.add("statistics.manaMax", GetStatistics().GetStatistic(StatisticType::kMana)->GetMaxValue());
  ptree.add("statistics.armor", GetStatistics().GetStatistic(StatisticType::kArmor)->GetValue());

  return ptree;
}

void Player::Deserialize(const boost::property_tree::ptree &ptree) {
  SetId(ptree.get<int>("id"));
  SetName(ptree.get<std::string>("name"));

}

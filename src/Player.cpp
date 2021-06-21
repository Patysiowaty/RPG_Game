#include "Player.hpp"
#include "ItemBuilder.hpp"
#include <boost/uuid/uuid_io.hpp>

Player::Player()
	: Character(), items_interactor_{&player_inventory_, &player_equipment_, &player_level_, GetId()} {
  items_interactor_.RegisterHandler(&player_attributes_);
  items_interactor_.RegisterHandler(&player_statistics_);
  player_level_.RegisterHandler(&player_attributes_);
  player_level_.RegisterHandler(&player_statistics_);
  player_attributes_.RegisterHandler(&player_statistics_);
}

void Player::Attack() {

}

void Player::MoveCharacter() {

}

boost::property_tree::ptree Player::Serialize() {
  boost::property_tree::basic_ptree<std::string, std::string> ptree;
  ptree.put("id", *GetId());
  ptree.put("uuid", boost::uuids::to_string(GetUuid()));
  ptree.put("name", GetName());
  ptree.put("gender", static_cast<int>(GetGender()));
  ptree.put("race", static_cast<int>(GetRace()));
  ptree.put("class", static_cast<int>(GetClass()));
  ptree.put("level", player_level_.GetLevel());
  ptree.put("experience", player_level_.GetExperience().first);

  ptree.put("attributes.strength", player_attributes_.GetAttribute(AttributeType::kStrength)->GetValue());
  ptree.add("attributes.dexterity", player_attributes_.GetAttribute(AttributeType::kDexterity)->GetValue());
  ptree.add("attributes.vitality", player_attributes_.GetAttribute(AttributeType::kVitality)->GetValue());
  ptree.add("attributes.intelligence", player_attributes_.GetAttribute(AttributeType::kIntelligence)->GetValue());

  ptree.put("statistics.attack", player_statistics_.GetStatistic(StatisticType::kAttack)->GetValue());
  ptree.add("statistics.attackMax", player_statistics_.GetStatistic(StatisticType::kAttack)->GetMaxValue());
  ptree.add("statistics.health", player_statistics_.GetStatistic(StatisticType::kHealth)->GetValue());
  ptree.add("statistics.healthMax", player_statistics_.GetStatistic(StatisticType::kHealth)->GetMaxValue());
  ptree.add("statistics.stamina", player_statistics_.GetStatistic(StatisticType::kStamina)->GetValue());
  ptree.add("statistics.staminaMax", player_statistics_.GetStatistic(StatisticType::kStamina)->GetMaxValue());
  ptree.add("statistics.mana", player_statistics_.GetStatistic(StatisticType::kMana)->GetValue());
  ptree.add("statistics.manaMax", player_statistics_.GetStatistic(StatisticType::kMana)->GetMaxValue());
  ptree.add("statistics.armor", player_statistics_.GetStatistic(StatisticType::kArmor)->GetValue());

  ptree.put("inventorySize", player_inventory_.GetInventoryAvailableTabs());
  return ptree;
}

void Player::Deserialize(const boost::property_tree::ptree &ptree) {
  SetId(ptree.get<int>("id"));
  SetName(ptree.get<std::string>("name"));
  SetGender(CharacterGender(ptree.get<int>("gender")));
  SetRace(CharacterRace(ptree.get<int>("race")));
  SetClass(CharacterClass(ptree.get<int>("class")));
  player_level_.SetLevel(ptree.get<uint16_t>("level"));
  player_level_.SetExperience(ptree.get<std::size_t>("experience"));
  player_attributes_.GetAttribute(AttributeType::kStrength)->SetValue(ptree.get<int32_t>("attributes.strength"));
  player_attributes_.GetAttribute(AttributeType::kDexterity)->SetValue(ptree.get<int32_t>("attributes.dexterity"));
  player_attributes_.GetAttribute(AttributeType::kVitality)->SetValue(ptree.get<int32_t>("attributes.vitality"));
  player_attributes_.GetAttribute(AttributeType::kIntelligence)->SetValue(ptree.get<int32_t>("attributes.intelligence"));
  player_statistics_.GetStatistic(StatisticType::kAttack)->SetMaxMinValue(ptree.get<std::int32_t>("statistics.attackMax"),
																		  ptree.get<std::int32_t>("statistics.attack"));
  player_statistics_.GetStatistic(StatisticType::kHealth)->SetMaxMinValue(ptree.get<std::int32_t>("statistics.healthMax"),
																		  ptree.get<std::int32_t>("statistics.health"));
  player_statistics_.GetStatistic(StatisticType::kStamina)->SetMaxMinValue(ptree.get<std::int32_t>(
	  "statistics.staminaMax"),
																		   ptree.get<std::int32_t>("statistics.stamina"));
  player_statistics_.GetStatistic(StatisticType::kMana)->SetMaxMinValue(ptree.get<std::int32_t>("statistics.manaMax"),
																		ptree.get<std::int32_t>("statistics.mana"));
  player_statistics_.GetStatistic(StatisticType::kArmor)->SetMaxMinValue(ptree.get<std::int32_t>("statistics.armor"),
																		 ptree.get<std::int32_t>("statistics.armor"));
  player_inventory_.SetInventoryAvailableTabs(ptree.get<std::uint16_t>("inventorySize"));

  ItemBuilder item_builder;
  const auto &inventory = ptree.get_child("inventory");
  for (const auto&[first, second]: inventory) {
	const auto kTemplateId = second.get<std::uint32_t>("templateId");
	const auto kItemId = second.get<std::uint32_t>("itemId");
	player_inventory_.PutItem(item_builder.MakeItem(kTemplateId, kItemId), second.get<int>("position"));
  }

}

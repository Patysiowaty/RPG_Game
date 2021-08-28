#include "Player.hpp"
#include "../game_core/ItemBuilder.hpp"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <SFML/System/Clock.hpp>

Player::Player()
	: uuid_{boost::uuids::random_generator()()},
	  items_interactor_{player_inventory_, player_equipment_, player_level_, id_} {
  items_interactor_.RegisterHandler(&player_attributes_);
  items_interactor_.RegisterHandler(&player_statistics_);
  player_level_.RegisterHandler(&player_attributes_);
  player_level_.RegisterHandler(&player_statistics_);
  player_attributes_.RegisterHandler(&player_statistics_);
}

void Player::SetName(const std::string &value) {
  name_ = value;
}

void Player::SetId(uint32_t value) {
  id_ = value;
}

void Player::SetGender(CharacterGender value) {
  gender_ = value;
}

void Player::SetRace(CharacterRace value) {
  race_ = value;
}

void Player::SetClass(CharacterClass value) {
  class_ = value;
}

const std::string &Player::GetName() const {
  return name_;
}

uint32_t Player::GetId() const {
  return id_;
}

boost::uuids::uuid Player::GetUuid() const {
  return uuid_;
}

CharacterClass Player::GetClass() const {
  return class_;
}

CharacterGender Player::GetGender() const {
  return gender_;
}

CharacterRace Player::GetRace() const {
  return race_;
}

boost::property_tree::ptree Player::Serialize() const {
  boost::property_tree::basic_ptree<std::string, std::string> ptree;
  ptree.put("id", id_);
  ptree.put("uuid", boost::uuids::to_string(uuid_));
  ptree.put("name", name_);
  ptree.put("gender", static_cast<int>(gender_));
  ptree.put("race", static_cast<int>(race_));
  ptree.put("class", static_cast<int>(class_));
  ptree.put("level", player_level_.GetLevel());
  ptree.put("experience", player_level_.GetExperience().first);

  ptree.put("attributes.strength", player_attributes_.GetAttribute(AttributeType::kStrength)->GetValue());
  ptree.add("attributes.dexterity", player_attributes_.GetAttribute(AttributeType::kDexterity)->GetValue());
  ptree.add("attributes.vitality", player_attributes_.GetAttribute(AttributeType::kVitality)->GetValue());
  ptree.add("attributes.intelligence", player_attributes_.GetAttribute(AttributeType::kIntelligence)->GetValue());

  ptree.put("statistics.attack", player_statistics_.GetStatistic(StatisticType::kAttack)->GetValue());
  ptree.add("statistics.armor", player_statistics_.GetStatistic(StatisticType::kArmor)->GetValue());

  ptree.add("statistics.health", player_statistics_.GetStatistic(StatisticType::kHealth)->GetValue());
  ptree.add("statistics.healthMax", player_statistics_.GetStatistic(StatisticType::kHealth)->GetMaxValue());
  ptree.add("statistics.stamina", player_statistics_.GetStatistic(StatisticType::kStamina)->GetValue());
  ptree.add("statistics.staminaMax", player_statistics_.GetStatistic(StatisticType::kStamina)->GetMaxValue());
  ptree.add("statistics.mana", player_statistics_.GetStatistic(StatisticType::kMana)->GetValue());
  ptree.add("statistics.manaMax", player_statistics_.GetStatistic(StatisticType::kMana)->GetMaxValue());

  ptree.put("inventorySize", player_inventory_.GetInventoryAvailableTabs());
  ptree.put("position.x", sf::Transformable::getPosition().x);
  ptree.put("position.y", sf::Transformable::getPosition().y);
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

  player_attributes_.GetAttribute(AttributeType::kStrength)->SetValue(ptree.get<std::int32_t>("attributes.strength"));
  player_attributes_.GetAttribute(AttributeType::kDexterity)->SetValue(ptree.get<std::int32_t>("attributes.dexterity"));
  player_attributes_.GetAttribute(AttributeType::kVitality)->SetValue(ptree.get<std::int32_t>("attributes.vitality"));
  player_attributes_.GetAttribute(AttributeType::kIntelligence)->SetValue(ptree.get<std::int32_t>(
	  "attributes.intelligence"));

  player_statistics_.GetStatistic(StatisticType::kAttack)->SetValue(ptree.get<std::int32_t>("statistics.attack"));
  player_statistics_.GetStatistic(StatisticType::kHealth)->SetMaxValue(ptree.get<std::int32_t>(
	  "statistics.healthMax"));
  player_statistics_.GetStatistic(StatisticType::kHealth)->SetValue(ptree.get<std::int32_t>("statistics.health"));

  player_statistics_.GetStatistic(StatisticType::kStamina)->SetMaxValue(ptree.get<std::int32_t>(
	  "statistics.staminaMax"));
  player_statistics_.GetStatistic(StatisticType::kStamina)->SetValue(ptree.get<std::int32_t>("statistics.stamina"));

  player_statistics_.GetStatistic(StatisticType::kMana)->SetMaxValue(ptree.get<std::int32_t>("statistics.manaMax"));
  player_statistics_.GetStatistic(StatisticType::kMana)->SetValue(ptree.get<std::int32_t>("statistics.mana"));

  player_statistics_.GetStatistic(StatisticType::kArmor)->SetMaxValue(ptree.get<std::int32_t>("statistics.armor"));
  player_statistics_.GetStatistic(StatisticType::kArmor)->SetValue(ptree.get<std::int32_t>("statistics.armor"));

  player_inventory_.SetInventoryAvailableTabs(ptree.get<std::uint16_t>("inventorySize"));

  ItemBuilder item_builder;
  const auto &inventory = ptree.get_child("inventory");
  for (const auto&[first, second]: inventory) {
	const auto kTemplateId = second.get<std::uint32_t>("templateId");
	const auto kItemId = second.get<std::uint32_t>("itemId");
	player_inventory_.PutItem(item_builder.MakeItem(kTemplateId, kItemId), second.get<int>("position"));
  }

  sf::Transformable::setPosition(ptree.get<float>("position.x"), ptree.get<float>("position.y"));
}

std::int32_t Player::Attack() const {
  const auto &attack = player_statistics_.GetStatistic(StatisticType::kAttack);
  const auto min_value = attack->GetValue();
  const auto max_value = attack->GetMaxValue();

  //TODO: implement random
  return std::rand() % (max_value - min_value) + min_value;
}

void Player::TakeDamage(std::int32_t value) {
  const auto &health = player_statistics_.GetStatistic(StatisticType::kHealth);
  health->SubtractValue(value);
  if (health->GetValue() == 0)
	is_alive_ = false;
}

std::int32_t Player::GetCurrentHealth() const {
  return player_statistics_.GetStatistic(StatisticType::kHealth)->GetValue();
}

void Player::SetBattleState(BattleStates battle_state) {
  battle_state_ = battle_state;
}

bool Player::IsAlive() const {
  return is_alive_;
}

std::uint16_t Player::GetLevel() const {
  return player_level_.GetLevel();
}

void Player::AddExperience(std::size_t value) {
  player_level_.AddExperience(value);
}

void Player::Update(float delta_time) {

}


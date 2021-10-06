#include "ItemCreator.hpp"
#include <stdexcept>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

std::uint32_t ItemCreator::next_item_id_{1};

ItemCreator::ItemCreator(uint32_t next_item_id) {
  if (next_item_id)
	next_item_id_ = next_item_id;
}

std::shared_ptr<Item> ItemCreator::MakeItem(std::uint32_t template_id) {
  template_id_ = std::to_string(template_id);
  ReadTemplateFromFile();

  if (item_) item_.reset();
  item_ = std::make_shared<Item>(next_item_id_);

  try {
	const auto kItemName = item_template_.get<std::string>("name");
	item_->SetName(kItemName);

	const auto kIconPath = item_template_.get<std::string>("icon");
	item_->SetIcon(kIconPath);

	const auto kItemType = item_template_.get<int>("type");
	item_->SetItemType(ItemType(kItemType));

	const auto kItemRarity = item_template_.get<int>("rarity");
	item_->SetRarity(ItemRarity(kItemRarity));

	const auto kLevelRequire = item_template_.get<std::uint16_t>("levelRequire");
	item_->SetLevelRequirement(kLevelRequire);

	//TODO: add checking
	const auto kClassesReq = item_template_.get_child("classRequire");
	std::vector<CharacterClass> class_list;

	for (const auto &array: kClassesReq) {
	  const auto temp = array.second.get<int>("");
	  class_list.emplace_back(CharacterClass(temp));
	}

	item_->SetCharacterClassRequirement(class_list);

	if (const auto kIterator = item_template_.find("description"); kIterator != item_template_.not_found()) {
	  const auto kDesc = kIterator->second.get<std::string>("");
	  item_->SetDescription(kDesc);
	}

	BuildAttributes();
	BuildStatistics();

  } catch (boost::property_tree::ptree_bad_path &ptree_bad_path) {
	std::cerr << "ItemCreator::MakeItem -> failed build template id: " + template_id_ + "\n"
			  << ptree_bad_path.path<std::string>() << "\n" << ptree_bad_path.what() << "\n";
	return nullptr;
  } catch (std::exception &e) {
	std::cerr << "ItemCreator::MakeItem -> failed build template id: " + template_id_ + "\n" << e.what() << "\n";
	return nullptr;
  }

  next_item_id_++;
  return item_;
}

void ItemCreator::ReadTemplateFromFile() {
  boost::property_tree::ptree data;
  boost::property_tree::read_json("../game_data/item_templates.json", data);
  if (data.find(template_id_) == data.not_found())
	throw std::invalid_argument{"ItemCreator::SetTemplateId -> not found template " + template_id_};
  item_template_ = data.get_child(template_id_);
}

void ItemCreator::BuildAttributes() {
  if (item_template_.find("attributes") == item_template_.not_found()) return;
  const auto kAttributes = item_template_.get_child("attributes");

  const std::vector<std::pair<std::string, AttributeType>> pairs = {{"strength", AttributeType::kStrength},
																	{"dexterity", AttributeType::kDexterity},
																	{"vitality", AttributeType::kVitality},
																	{"intelligence", AttributeType::kIntelligence}};

  std::vector<Attribute> item_attributes;
  for (const auto&[name, type]: pairs) {
	if (kAttributes.find(name) == kAttributes.not_found()) continue;
	const auto kValue = kAttributes.get<std::int32_t>(name);
	item_attributes.emplace_back(type, kValue);
  }

  item_->SetAttributes(item_attributes);
}

std::shared_ptr<Item> ItemCreator::MakeItem(std::uint32_t template_id, std::uint32_t item_id) {
  template_id_ = std::to_string(template_id);
  ReadTemplateFromFile();

  if (item_) item_.reset();
  item_ = std::make_shared<Item>(next_item_id_);

  try {
	const auto kItemName = item_template_.get<std::string>("name");
	item_->SetName(kItemName);

	const auto kIconPath = item_template_.get<std::string>("icon");
	item_->SetIcon(kIconPath);

	const auto kItemType = item_template_.get<int>("type");
	item_->SetItemType(ItemType(kItemType));

	const auto kItemRarity = item_template_.get<int>("rarity");
	item_->SetRarity(ItemRarity(kItemRarity));

	const auto kLevelRequire = item_template_.get<std::uint16_t>("levelRequire");
	item_->SetLevelRequirement(kLevelRequire);

	//TODO: add checking
	const auto kClassesReq = item_template_.get_child("classRequire");
	std::vector<CharacterClass> class_list;

	for (const auto &array: kClassesReq) {
	  const auto temp = array.second.get<int>("");
	  class_list.emplace_back(CharacterClass(temp));
	}

	item_->SetCharacterClassRequirement(class_list);

	if (const auto kIterator = item_template_.find("description"); kIterator != item_template_.not_found()) {
	  const auto kDesc = kIterator->second.get<std::string>("");
	  item_->SetDescription(kDesc);
	}

	BuildAttributes();
	BuildStatistics();

  } catch (boost::property_tree::ptree_bad_path &ptree_bad_path) {
	std::cerr << "ItemCreator::BuildRawItem() -> failed build template id: " + template_id_ + "\n"
			  << ptree_bad_path.path<std::string>() << "\n" << ptree_bad_path.what() << "\n";
	return nullptr;
  } catch (std::exception &e) {
	std::cerr << "ItemCreator::BuildRawItem() -> failed build template id: " + template_id_ + "\n" << e.what() << "\n";
	return nullptr;
  }

  item_->SetId(item_id);
  return item_;
}

void ItemCreator::BuildStatistics() {
  if (item_template_.find("stats") == item_template_.not_found()) return;
  const auto kStatistics = item_template_.get_child("stats");

  const std::vector<std::pair<std::string, StatisticType>> pairs = {
	  {"attack", StatisticType::kAttack}, {"magicAttack", StatisticType::kMagicAttack},
	  {"health", StatisticType::kHealth}, {"armor", StatisticType::kArmor},
	  {"stamina", StatisticType::kStamina}, {"mana", StatisticType::kMana},
	  {"magicResistance", StatisticType::kMagicResistance}, {"evadeRatio", StatisticType::kEvadeRatio},
	  {"criticalStrikeRatio", StatisticType::kCriticalStrikeRatio},
	  {"criticalStrikeForce", StatisticType::kCriticalStrikeForce}};

  std::vector<Statistic> statistics_list;
  for (const auto&[name, type]: pairs) {
	if (kStatistics.find(name) == kStatistics.not_found()) continue;
	const auto kValue = kStatistics.get<std::int32_t>(name);
	statistics_list.emplace_back(type, kValue);
  }

  item_->SetStatistics(statistics_list);
}





#include "ItemBuilder.hpp"
#include <stdexcept>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <cmath>

std::uint32_t ItemBuilder::next_item_id_ = 1;

ItemBuilder::ItemBuilder(uint32_t next_item_id) {
  if (!next_item_id)
	next_item_id_ = next_item_id;
}

void ItemBuilder::SetTemplateId(std::uint32_t template_id) {
  template_id_ = std::to_string(template_id);
}

std::shared_ptr<Item> ItemBuilder::MakeItem(std::uint32_t template_id) {
  SetTemplateId(template_id);
  ReadTemplateFromFile();
  if (item_) item_.reset();
  item_ = std::make_shared<Item>(next_item_id_);

  if (!BuildRawItem()) {
	item_.reset();
	return item_;
  }
  if (!BuildAttributes()) {
	item_.reset();
	return item_;
  }
  if (!BuildStatistics()) {
	item_.reset();
	return item_;
  }
  next_item_id_++;
  return item_;
}

std::shared_ptr<Item> ItemBuilder::MakeItem(std::uint32_t template_id, std::uint32_t item_id) {
  SetTemplateId(template_id);
  ReadTemplateFromFile();
  if (item_) item_.reset();
  item_ = std::make_shared<Item>(item_id);

  if (!BuildRawItem()) {
	item_.reset();
	return item_;
  }
  if (!BuildAttributes()) {
	item_.reset();
	return item_;
  }
  if (!BuildStatistics()) {
	item_.reset();
	return item_;
  }

  return item_;
}

bool ItemBuilder::BuildRawItem() {
  try {
	const auto item_name = item_template_.get<std::string>("name");
	item_->SetName(item_name);

	const auto item_type = item_template_.get<int>("type");
	item_->SetItemType(ItemType(item_type));

	const auto item_rarity = item_template_.get<int>("rarity");
	item_->SetRarity(ItemRarity(item_rarity));

	const auto level_require = item_template_.get<std::uint16_t>("levelRequire");
	item_->SetLevelRequirement(level_require);

	const auto classes_req = item_template_.get_child("classRequire");
	std::vector<CharacterClass> class_list;

	for (const auto &array: classes_req) {
	  const auto temp = array.second.get<int>("");
	  class_list.push_back(CharacterClass(temp));
	}
	item_->SetCharacterClassRequirement(class_list);

	if (const auto it = item_template_.find("description"); it != item_template_.not_found()) {
	  const auto desc = it->second.get<std::string>("");
	  item_->SetDescription(desc);
	}

	return true;
  } catch (boost::property_tree::ptree_bad_path &ptree_bad_path) {
	std::cerr << "ItemBuilder::BuildRawItem() -> failed build template id: " + template_id_ + "\n"
			  << ptree_bad_path.path<std::string>() << "\n" << ptree_bad_path.what() << "\n";
	return false;
  } catch (std::exception &e) {
	std::cerr << "ItemBuilder::BuildRawItem() -> failed build template id: " + template_id_ + "\n" << e.what() << "\n";
	return false;
  }
}

bool ItemBuilder::BuildAttributes() {
  const std::vector<std::pair<std::string, AttributeType>> pairs = {{"strength", AttributeType::kStrength},
																	{"vitality", AttributeType::kVitality},
																	{"dexterity", AttributeType::kDexterity},
																	{"intelligence", AttributeType::kIntelligence}};
  try {
	if (item_template_.find("attributes") == item_template_.not_found()) return true;
	std::vector<Attribute> item_attributes;

	for (const auto&[name, type] : pairs)
	  if (auto ptr = GetAttributeValue(name, type); ptr != nullptr)
		item_attributes.emplace_back(*ptr);

	item_->SetAttributes(item_attributes);
	return true;
  } catch (boost::property_tree::ptree_bad_path &ptree_bad_path) {
	std::cerr << "ItemBuilder::BuildAttributes() -> failed build template id: " + template_id_ + "\n"
			  << ptree_bad_path.path<std::string>() << "\n" << ptree_bad_path.what() << "\n";
	return false;
  } catch (std::exception &e) {
	std::cerr << "ItemBuilder::BuildAttributes() -> failed build template id: " + template_id_ + "\n" << e.what()
			  << "\n";
	return false;
  }
}

bool ItemBuilder::BuildStatistics() {
  try {

	return true;
  } catch (boost::property_tree::ptree_bad_path &ptree_bad_path) {
	std::cerr << "ItemBuilder::BuildStatistics() -> failed build item id: " + template_id_ + "\n"
			  << ptree_bad_path.path<std::string>() << "\n" << ptree_bad_path.what() << "\n";
	return false;
  } catch (std::exception &e) {
	std::cerr << "ItemBuilder::BuildStatistics() -> failed build template id: " + template_id_ + "\n" << e.what()
			  << "\n";
	return false;
  }
}

int32_t ItemBuilder::CalculateAttribute(int value) {
  const auto kBonusModifier = 1.1f;
  const auto kLevelModifier = item_->GetLevelRequirement();
  const auto kRarityModifier = static_cast<int>(item_->GetItemRarity());

  return std::ceil(kLevelModifier * kRarityModifier * value / std::pow(kBonusModifier, value));
}

std::unique_ptr<Attribute> ItemBuilder::GetAttributeValue(const std::string &attribute_name,
														  AttributeType attribute_type) {
  const auto template_attributes = item_template_.get_child("attributes");
  if (const auto kFind = template_attributes.find(attribute_name); kFind != template_attributes.not_found()) {
	const auto kValue = CalculateAttribute(kFind->second.get<int>(""));
	return std::make_unique<Attribute>(attribute_type, kValue);
  }
  return nullptr;
}

void ItemBuilder::ReadTemplateFromFile() {
  boost::property_tree::ptree data;
  boost::property_tree::read_json("../game_data/item_templates.json", data);
  if (data.find(template_id_) == data.not_found())
	throw std::invalid_argument{"ItemBuilder::SetTemplateId -> not found template " + template_id_};
  item_template_ = data.get_child(template_id_);
}





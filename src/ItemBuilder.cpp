#include "ItemBuilder.hpp"
#include <stdexcept>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

std::uint32_t ItemBuilder::next_item_id_ = 1;

ItemBuilder::ItemBuilder(std::uint32_t template_id, uint32_t next_item_id) {
  item_ = std::make_shared<Item>();
  template_id_ = std::to_string(template_id);
  boost::property_tree::ptree data;
  boost::property_tree::read_json("../game_data/item_templates.json", data);
  if (data.find(template_id_) == data.not_found())
	throw std::invalid_argument{"ItemBuilder::ItemBuilder -> not found template " + template_id_};
  item_template_ = data.get_child(template_id_);
  if (!next_item_id)
	next_item_id_ = next_item_id;
}

std::shared_ptr<Item> ItemBuilder::MakeItem() {
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
  if (!BuildOptionalData()) {
	item_.reset();
	return item_;
  }

  next_item_id_++;
  return item_;
}

bool ItemBuilder::BuildRawItem() {
  try {
	item_->SetId(next_item_id_);

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
	std::cerr << "ItemBuilder::BuildRawItem() -> failed build item id: " + template_id_ + "\n"
			  << ptree_bad_path.path<std::string>() << "\n" << ptree_bad_path.what() << "\n";
	return false;
  } catch (std::exception &e) {
	std::cerr << "ItemBuilder::BuildRawItem() -> failed build item id: " + template_id_ + "\n" << e.what() << "\n";
	return false;
  }
}

bool ItemBuilder::BuildAttributes() {
  try {
	if (item_template_.find("attributes") == item_template_.not_found()) return true;

	const auto template_attributes = item_template_.get_child("statistics");

	std::vector<Attribute> item_attributes;
	int iteration = 0;
	for (const auto &attribute: template_attributes) {
	  iteration++;
	  const auto attribute_value = attribute.second.get<int>("");
	  if (attribute_value == 0) continue;
	  const std::uint32_t item_attr_value = CalculateAttribute(attribute_value);
	  item_attributes.emplace_back(AttributeType(iteration), item_attr_value);
	}
	item_->SetAttributes(item_attributes);
	return true;
  } catch (boost::property_tree::ptree_bad_path &ptree_bad_path) {
	std::cerr << "ItemBuilder::BuildAttributes() -> failed build item id: " + template_id_ + "\n"
			  << ptree_bad_path.path<std::string>() << "\n" << ptree_bad_path.what() << "\n";
	return false;
  } catch (std::exception &e) {
	std::cerr << "ItemBuilder::BuildAttributes() -> failed build item id: " + template_id_ + "\n" << e.what() << "\n";
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
	std::cerr << "ItemBuilder::BuildStatistics() -> failed build item id: " + template_id_ + "\n" << e.what() << "\n";
	return false;
  }
}

int32_t ItemBuilder::CalculateAttribute(int value) {
  const auto kBonusModifier = 1.1f;
  const auto kLevelModifier = item_->GetLevelRequirement();
  const auto kRarityModifier = static_cast<int>(item_->GetItemRarity());

  return std::ceil(kLevelModifier * kRarityModifier * value / std::pow(kBonusModifier, value));
}



#include "ItemBuilder.hpp"
#include <stdexcept>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

ItemBuilder::ItemBuilder(std::uint32_t template_id) {
  item_ = std::make_shared<Item>();
  template_id_ = std::to_string(template_id);
  boost::property_tree::ptree data;
  boost::property_tree::read_json("../game_data/item_templates.json", data);
  if (data.find(template_id_) == data.not_found())
	throw std::invalid_argument{"ItemBuilder::ItemBuilder -> not found template " + template_id_};
  item_template_ = data.get_child(template_id_);
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

	return true;
  } catch (std::exception &e) {
	std::cerr << e.what() << "\n";
	return false;
  }
}

bool ItemBuilder::BuildAttributes() {
  try {

	return true;
  } catch (std::exception &e) {
	std::cerr << e.what() << "\n";
	return false;
  }
}

bool ItemBuilder::BuildStatistics() {
  try {

	return true;
  } catch (std::exception &e) {
	std::cerr << e.what() << "\n";
	return false;
  }
}

bool ItemBuilder::BuildOptionalData() {
  try {
	if (const auto it = item_template_.find("description"); it != item_template_.not_found()) {
	  const auto desc = it->second.get<std::string>("");
	  item_->SetDescription(desc);
	}
	return true;
  } catch (std::exception &e) {
	std::cerr << e.what() << "\n";
	return false;
  }
}



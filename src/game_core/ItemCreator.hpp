#ifndef ITEMCREATOR_HPP
#define ITEMCREATOR_HPP

#include "../interfaces/IItemBuilder.hpp"
#include <boost/property_tree/ptree.hpp>

class ItemCreator {
 public:
  explicit ItemCreator(std::uint32_t next_item_id = 0);
  std::shared_ptr<Item> MakeItem(std::uint32_t template_id);
  std::shared_ptr<Item> MakeItem(std::uint32_t template_id, std::uint32_t item_id);

 private:
  void ReadTemplateFromFile();
  void BuildAttributes();

 private:
  static std::uint32_t next_item_id_;

  std::shared_ptr<Item> item_;
  std::string template_id_;
  boost::property_tree::ptree item_template_;
};

#endif //ITEMCREATOR_HPP

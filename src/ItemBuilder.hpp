#ifndef ITEMBUILDER_HPP
#define ITEMBUILDER_HPP

#include "interfaces/IItemBuilder.hpp"
#include <boost/property_tree/ptree.hpp>

class ItemBuilder : private IItemBuilder {
 public:
  explicit ItemBuilder(std::uint32_t template_id, uint32_t next_item_id = 0);
  std::shared_ptr<Item> MakeItem() override;

 private:
  bool BuildRawItem() override;
  bool BuildAttributes() override;
  bool BuildStatistics() override;

 private:
  std::int32_t CalculateAttribute(int value);
  std::unique_ptr<Attribute> GetAttributeValue(const std::string &attribute_name, AttributeType attribute_type);

 private:
  static std::uint32_t next_item_id_;

  std::shared_ptr<Item> item_;
  std::string template_id_;
  boost::property_tree::ptree item_template_;
};

#endif //ITEMBUILDER_HPP

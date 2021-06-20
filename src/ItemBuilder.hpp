#ifndef ITEMBUILDER_HPP
#define ITEMBUILDER_HPP

#include "interfaces/IItemBuilder.hpp"
#include <boost/property_tree/ptree.hpp>

class ItemBuilder : private IItemBuilder {
 public:
  explicit ItemBuilder(std::uint32_t next_item_id = 0);
  void SetTemplateId(std::uint32_t template_id);
  std::shared_ptr<Item> MakeItem(std::uint32_t template_id) override;
  std::shared_ptr<Item> MakeItem(std::uint32_t template_id, std::uint32_t item_id);

 private:
  bool BuildRawItem() override;
  bool BuildAttributes() override;
  bool BuildStatistics() override;

 private:
  std::int32_t CalculateAttribute(std::int32_t value);
  std::unique_ptr<Attribute> GetAttributeValue(const std::string &attribute_name, AttributeType attribute_type);
  void ReadTemplateFromFile();

 private:
  static std::uint32_t next_item_id_;

  std::shared_ptr<Item> item_;
  std::string template_id_;
  boost::property_tree::ptree item_template_;
};

#endif //ITEMBUILDER_HPP

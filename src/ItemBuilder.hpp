#ifndef ITEMBUILDER_HPP
#define ITEMBUILDER_HPP

#include "interfaces/IItemBuilder.hpp"
#include <boost/property_tree/ptree.hpp>

class ItemBuilder : private IItemBuilder {
 public:
  explicit ItemBuilder(std::uint32_t template_id);
  std::shared_ptr<Item> MakeItem() override;

 private:
  bool BuildRawItem() override;
  bool BuildAttributes() override;
  bool BuildStatistics() override;
  bool BuildOptionalData() override;

 private:
  std::shared_ptr<Item> item_;
  std::string template_id_;
  boost::property_tree::ptree item_template_;
};

#endif //ITEMBUILDER_HPP

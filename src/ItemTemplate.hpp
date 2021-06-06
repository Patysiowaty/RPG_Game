#ifndef ITEMTEMPLATE_HPP
#define ITEMTEMPLATE_HPP

#include <string>
#include <vector>
class ItemTemplate {
 public:
  ItemTemplate();
  ItemTemplate(uint32_t id, const std::string &template_data);

  void SetTemplateId(uint32_t id);
  void SetTemplateData(const std::string &data);

  const std::string &GetItemTemplateData() const;

 private:
  uint32_t template_id_ = 0;
  std::string item_template_data_;
};

#endif //ITEMTEMPLATE_HPP

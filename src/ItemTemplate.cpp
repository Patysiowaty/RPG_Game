#include "ItemTemplate.hpp"

ItemTemplate::ItemTemplate() {

}

ItemTemplate::ItemTemplate(uint32_t id, const std::string &template_data) {
  SetTemplateId(id);
  SetTemplateData(template_data);
}

void ItemTemplate::SetTemplateId(uint32_t id) {
  template_id_ = id;
}

void ItemTemplate::SetTemplateData(const std::string &data) {
  item_template_data_ = data;
}

const std::string &ItemTemplate::GetItemTemplateData() const {
  return item_template_data_;
}



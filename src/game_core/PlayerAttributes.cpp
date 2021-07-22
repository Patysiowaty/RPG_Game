#include "PlayerAttributes.hpp"
#include <stdexcept>

PlayerAttributes::PlayerAttributes(int32_t strength, int32_t dexterity, int32_t vitality, int32_t intelligence) {
  attributes_.emplace_back(std::make_unique<Attribute>(AttributeType::kStrength, strength));
  attributes_.emplace_back(std::make_unique<Attribute>(AttributeType::kDexterity, dexterity));
  attributes_.emplace_back(std::make_unique<Attribute>(AttributeType::kVitality, vitality));
  attributes_.emplace_back(std::make_unique<Attribute>(AttributeType::kIntelligence, intelligence));
}

const std::unique_ptr<Attribute> &PlayerAttributes::GetAttribute(AttributeType attribute_type) const {
  const auto it = std::find_if(attributes_.cbegin(), attributes_.cend(),
							   [&](const std::unique_ptr<Attribute> &value) {
								 return attribute_type == value->GetType();
							   });

  if (it == attributes_.cend()) throw std::invalid_argument{"PlayerAttributes::GetAttribute -> no attribute"};

  return *it;
}

void PlayerAttributes::RaiseAttributes() {
  for (const auto &attribute : attributes_)
	attribute->AddValue(kAttributesBaseModifier);

  for (const auto handler: handlers_)
	handler->OnAttributesUpdate(attributes_);
}

void PlayerAttributes::DowngradeAttributes() {
  for (const auto &attribute : attributes_)
	attribute->SubtractValue(kAttributesBaseModifier);

  for (const auto handler: handlers_)
	handler->OnAttributesUpdate(attributes_);
}

void PlayerAttributes::AddAttribute(AttributeType attribute_type, std::int32_t value) {
  attributes_.emplace_back(std::make_unique<Attribute>(attribute_type, value));
}

void PlayerAttributes::SetAttributes(const std::vector<std::int32_t> &attributes) {
  for (int i = 0; i < attributes.size(); ++i)
	attributes_.at(i)->SetValue(attributes.at(i));
}

void PlayerAttributes::RegisterHandler(IAttributesHandler *handler) {
  handlers_.push_back(handler);
}

void PlayerAttributes::OnEquipItem(const std::shared_ptr<Item> &item) {
  const auto &item_attributes = item->GetAttributes();
  if (item_attributes.empty()) return;

  for (const auto &attribute: item_attributes) {
	if (const auto &find = GetAttribute(attribute.GetType()); find) {
	  find->AddValue(attribute.GetValue());
	  for (const auto handler: handlers_)
		handler->OnAttributeUpdate(find);
	}
  }
}

void PlayerAttributes::OnTakeOffItem(const std::shared_ptr<Item> &item) {
  const auto &item_attributes = item->GetAttributes();
  if (item_attributes.empty()) return;

  for (const auto &attribute: item_attributes) {
	if (const auto &find = GetAttribute(attribute.GetType()); find) {
	  find->SubtractValue(attribute.GetValue());
	  for (const auto handler: handlers_)
		handler->OnAttributeUpdate(find);
	}
  }
}

void PlayerAttributes::OnUsedItem(const std::shared_ptr<IConsumable> &item) {
  //TODO: Implement
  /*const auto &item_attributes = item->GetAfterConsumptionEffect();
  if (item_attributes.empty()) return;

  for (const auto &attribute: item_attributes) {
	if (const auto &find = GetAttribute(attribute.GetType()); find) {
	  find->AddValue(attribute.GetValue());
	  for (const auto handler: handlers_)
		handler->OnAttributeUpdate(find);
	}
  }*/
}

void PlayerAttributes::OnLevelRaise() {
  RaiseAttributes();
}

void PlayerAttributes::OnLevelDowngrade() {
  DowngradeAttributes();
}

void PlayerAttributes::OnLevelUpdate(int value) {
  if (value > 0)
	while (value--)
	  RaiseAttributes();
  else
	while (value++)
	  DowngradeAttributes();

}











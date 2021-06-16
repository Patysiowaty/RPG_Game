#include "CharacterAttributes.hpp"
#include <stdexcept>

CharacterAttributes::CharacterAttributes(int32_t strength, int32_t dexterity, int32_t vitality, int32_t intelligence) {
  attributes_.emplace_back(std::make_shared<Attribute>(AttributeType::kStrength, strength));
  attributes_.emplace_back(std::make_shared<Attribute>(AttributeType::kDexterity, dexterity));
  attributes_.emplace_back(std::make_shared<Attribute>(AttributeType::kVitality, vitality));
  attributes_.emplace_back(std::make_shared<Attribute>(AttributeType::kIntelligence, intelligence));
}

std::shared_ptr<Attribute> CharacterAttributes::GetAttribute(AttributeType attribute_type) {
  const auto it = std::find_if(attributes_.cbegin(), attributes_.cend(),
							   [&](const std::shared_ptr<Attribute> &value) {
								 return attribute_type == value->GetType();
							   });

  return it != attributes_.cend() ? *it : nullptr;
}

void CharacterAttributes::RaiseAttributes() {
  for (const auto &attribute : attributes_)
	attribute->AddValue(kAttributesBaseModifier);

  for (const auto handler: handlers_)
	handler->OnAttributesRaise();
}

void CharacterAttributes::LowerAttributes() {
  for (const auto &attribute : attributes_)
	attribute->SubtractValue(kAttributesBaseModifier);

  for (const auto handler: handlers_)
	handler->OnAttributesLower();
}

void CharacterAttributes::AddAttribute(AttributeType attribute_type, std::int32_t value) {
  attributes_.emplace_back(std::make_shared<Attribute>(attribute_type, value));
}

void CharacterAttributes::AddAttribute(std::shared_ptr<Attribute> attribute) {
  attributes_.emplace_back(std::move(attribute));
}

void CharacterAttributes::RegisterHandler(IAttributesHandler *handler) {
  handlers_.push_back(handler);
}

void CharacterAttributes::SetAttributes(const std::vector<std::int32_t> &attributes) {
  for (int i = 0; i < attributes.size(); ++i)
	attributes_.at(i)->SetValue(attributes.at(i));
}











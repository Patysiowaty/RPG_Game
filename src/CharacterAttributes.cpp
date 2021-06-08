#include "CharacterAttributes.hpp"
#include "Character.hpp"
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
  if (it == attributes_.cend()) throw std::invalid_argument{"CharacterAttributes::GetAttribute -> unknown attribute"};
  return *it;
}

void CharacterAttributes::RaiseAttributes() {
  for (const auto &attribute : attributes_)
	attribute->AddValue(kAttributesBaseModifier);
}

void CharacterAttributes::LowerAttributes() {
  for (const auto &attribute : attributes_)
	attribute->SubtractValue(kAttributesBaseModifier);
}











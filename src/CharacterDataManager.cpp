#include "CharacterDataManager.hpp"

CharacterDataManager::CharacterDataManager(CharacterStatistics *statistics,
										   CharacterAttributes *attributes,
										   CharacterLevel *level)
	: statistics_{statistics}, attributes_{attributes}, level_{level} {

}

void CharacterDataManager::OnLevelRaise() {
  attributes_->RaiseAttributes();
}

void CharacterDataManager::OnLevelDowngrade() {
  attributes_->LowerAttributes();
}

void CharacterDataManager::OnTakeOffItem(const std::shared_ptr<Item> &item) {
}

void CharacterDataManager::OnUsedItem(const std::shared_ptr<Item> &item) {

}

void CharacterDataManager::OnEquipItem(const std::shared_ptr<Item> &item) {

}

void CharacterDataManager::OnLevelUpdate(int value) {
  if (value > 0) {
	while (value) {
	  attributes_->RaiseAttributes();
	  --value;
	}
  } else {
	while (value) {
	  attributes_->LowerAttributes();
	  ++value;
	}
  }
}

void CharacterDataManager::OnAttributesRaise() {

}

void CharacterDataManager::OnAttributeRaise(AttributeType attribute_type) {
  switch (attribute_type) {
	case AttributeType::kStrength:
	case AttributeType::kVitality:
	case AttributeType::kDexterity:
	case AttributeType::kIntelligence:
	default:
	  break;
  }
}

void CharacterDataManager::OnAttributeLower(AttributeType attribute_type) {

}

void CharacterDataManager::OnAttributesLower() {

}


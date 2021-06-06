#include "CharacterDataUpdater.hpp"
CharacterDataUpdater::CharacterDataUpdater(CharacterStatistics *statistics, CharacterAttributes *attributes)
	: statistics_{statistics}, attributes_{attributes} {

}

void CharacterDataUpdater::OnEquipItem(const std::shared_ptr<Item> &item) {
  {
	attributes_->AddStrength(item->GetStrength());
	attributes_->AddDexterity(item->GetDexterity());
	attributes_->AddVitality(item->GetVitality());
	attributes_->AddIntelligence(item->GetIntelligence());
	switch (item->GetItemType()) {
	  case ItemType::kHelmet:
		break;
	  case ItemType::kRing:
		break;
	  case ItemType::kNecklace:
		break;
	  case ItemType::kGloves:
		break;
	  case ItemType::kWeapon: {
		auto weapon_item = std::dynamic_pointer_cast<SwordItem>(item);
		character_statistics_.AddAttack(weapon_item->GetAttackValue());
		break;
	  }
	  case ItemType::kArmor:
		break;
	  case ItemType::kOffHand:
		break;
	  case ItemType::kPants:
		break;
	  case ItemType::kBoots:
		break;
	  default:
		break;
	}

  }
}

void CharacterDataUpdater::OnTakeOffItem(const std::shared_ptr<Item> &item) {

}

void CharacterDataUpdater::OnUsedItem(const std::shared_ptr<Item> &item) {

}

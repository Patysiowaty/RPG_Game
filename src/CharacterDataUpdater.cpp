#include "CharacterDataUpdater.hpp"
CharacterDataUpdater::CharacterDataUpdater(CharacterStatistics *statistics, CharacterAttributes *attributes)
	: statistics_{statistics}, attributes_{attributes} {

}
void CharacterDataUpdater::OnLevelRaise() {
  attributes_->RaiseAttributes();
}

void CharacterDataUpdater::OnLevelDowngrade() {
  attributes_->LowerAttributes();
}

void CharacterDataUpdater::OnTakeOffItem(const std::shared_ptr<Item> &item) {
}

void CharacterDataUpdater::OnUsedItem(const std::shared_ptr<Item> &item) {

}

void CharacterDataUpdater::OnEquipItem(const std::shared_ptr<Item> &item) {

}

void CharacterDataUpdater::OnLevelUpdate(int value) {
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

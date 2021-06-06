#include "Player.hpp"

Player::Player() {

}

void Player::OnAttributesUpdate() {

}

void Player::OnLevelUpdate() {
  character_attributes_.RaiseBaseAttributes();
}

void Player::OnExperienceUpdate(bool is_leveled_up) {
  if (is_leveled_up) character_level_.LevelUp();
}



/*void Player::OnTakeOffItem(const std::shared_ptr<Item> &item) {
  character_attributes_.SubtractStrength(item->GetStrength());
  character_attributes_.SubtractDexterity(item->GetDexterity());
  character_attributes_.SubtractVitality(item->GetVitality());
  character_attributes_.SubtractIntelligence(item->GetIntelligence());
  character_inventory_.PutItem(item);
}*/

void Player::OnStatisticsUpdate() {

}

/*void Player::OnUsedItem(const std::shared_ptr<Item> &item) {
  if (item->GetItemType() == ItemType::kConsumptive) {
	auto cons_item = std::dynamic_pointer_cast<ConsumptiveItem>(item);
	if (const auto health_regen = cons_item->GetHealthRegen(); health_regen)
	  character_statistics_.RecoverHealth(health_regen);
	if (const auto mana_regen = cons_item->GetManaRegen(); mana_regen)
	  character_statistics_.RecoverMana(cons_item->GetManaRegen());
	if (const auto stamina_regen = cons_item->GetStaminaRegen(); stamina_regen)
	  character_statistics_.RecoverStamina(stamina_regen);
	if (const auto additional_health = cons_item->GetAdditionalHealthMax(); additional_health)
	  character_statistics_.IncreaseMaxHealth(additional_health);
	if (const auto additional_mana = cons_item->GetAdditionalMana(); additional_mana)
	  character_statistics_.IncreaseMaxMana(additional_mana);
	if (const auto additional_stamina = cons_item->GetAdditionalStamina(); additional_stamina)
	  character_statistics_.IncreaseMaxStamina(additional_stamina);
  }
}*/
void Player::Attack() {

}

void Player::MoveCharacter() {

}

void Player::OnBattleEnd(bool winner) {
player_experience_.AddExperience(12313);
}

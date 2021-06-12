#include "Player.hpp"

#include <utility>

Player::Player(std::uint32_t id, std::string character_name) : Character{id, std::move(character_name)} {

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

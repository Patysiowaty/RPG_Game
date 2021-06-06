#include "LevelManager.hpp"

LevelManager::LevelManager(CharacterLevel *level) : level_{level}, experience_{nullptr} {

}

LevelManager::LevelManager(CharacterLevel *level, PlayerExperience *experience) : level_{level},
																				  experience_{experience} {

}

LevelManagerEC LevelManager::AddExperience(std::int32_t value) {
  if (level_->HasMaximumLevel()) return LevelManagerEC::kCharacterHasMaximumLevel;
  experience_->AddExperience(value);

  while (experience_->ShouldLevelUp()) {
	if (!level_->LevelUp()) {
	  experience_->ShrinkToFit();
	  return LevelManagerEC::kNone;
	}
	experience_->CalculateNextLevelExperience(level_->GetLevel());
	for (auto handler : handlers_)
	  handler->OnLevelUpdate();
  }

  return LevelManagerEC::kNone;
}

LevelManagerEC LevelManager::IncreaseLevel(std::uint16_t) {
  if (level_->LevelUp()) return LevelManagerEC::kCharacterHasMaximumLevel;
  for (auto handler : handlers_)
	handler->OnLevelUpdate();
  return LevelManagerEC::kNone;
}




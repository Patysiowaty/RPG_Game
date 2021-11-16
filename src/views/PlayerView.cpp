#include "PlayerView.hpp"

PlayerView::PlayerView() {
  const auto kSize = static_cast<int>(ItemType::kSize);

  for (int i = 0; i < kSize; ++i) {
	equipped_items_.emplace(ItemType(i), false);
	items_icon_.emplace(ItemType(i), sf::Texture{});
	items_sprites_.emplace(ItemType(i), sf::Sprite{});
  }
}

void PlayerView::CreateSprite(const std::string &texture_path) {
  if (!player_icon_.loadFromFile(texture_path))
	throw std::invalid_argument{"PlayerView::CreateSprite -> failed load texture: " + texture_path};
  player_icon_.setSmooth(true);

  PlayerView::CreateAnimations();
  animation_manager_.PlayAnimation(AnimationType::kWalkDown);
}

void PlayerView::SetPosition(float x, float y) {
  sprite_.setPosition(x, y);
  for (auto &[first, second]: items_sprites_)
	second.setPosition(x, y);
}

void PlayerView::Update(float delta_time) {
  if (next_animation != AnimationType::kNone) {
	if (animation_manager_.GetCurrentAnimation() == AnimationType::kNone) {
	  animation_manager_.PlayAnimation(next_animation);
	  next_animation = AnimationType::kNone;
	}
  }
  animation_manager_.Update(delta_time);
}

void PlayerView::CreateAnimations() {
  animation_manager_.AddAnimation(AnimationType::kWalkDown, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 640, 576, 64), 9, 4, 1});

  animation_manager_.AddAnimation(AnimationType::kWalkLeft, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 576, 576, 64),
												   9, 4, 0});
  animation_manager_.AddAnimation(AnimationType::kWalkRight, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 704, 576, 64),
												   9, 4, 0});
  animation_manager_.AddAnimation(AnimationType::kWalkUp, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 512, 576, 64), 9,
												   4, 1});

  animation_manager_.AddAnimation(AnimationType::kSlashAttackUp, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 768, 384, 64), 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackLeft, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 832, 384, 64), 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackDown, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 896, 384, 64), 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackRight, sprite_, player_icon_,
								  AnimationDetails{sf::IntRect(0, 960, 384, 64), 6});

  CreateWeaponAnimation();
  CreateWalkAnimation();
  CreateAttackAnimation();
}

void PlayerView::CreateWeaponAnimation() {
  auto &slash_weapon_anim = items_sprites_.at(ItemType::kOneHandedSword);
  auto &slash_weapon_sheet = items_icon_.at(ItemType::kOneHandedSword);

  animation_manager_.AddAnimation(AnimationType::kSlashAttackDown, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 1024, 768, 128}, 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackLeft, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 896, 768, 128}, 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackUp, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 768, 768, 128}, 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackRight, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 1152, 768, 128}, 6});
}

void PlayerView::CreateWalkAnimation() {
  const auto kSize = static_cast<int>(ItemType::kSize) - 1;

  for (int i = 0; i < kSize; ++i) {
	const auto kItemType = ItemType(i);
	auto &sprite = items_sprites_.at(kItemType);
	auto &sheet = items_icon_.at(kItemType);

	animation_manager_.AddAnimation(AnimationType::kWalkDown, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 640, 576, 64), 9, 4, 1});
	animation_manager_.AddAnimation(AnimationType::kWalkLeft, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 576, 576, 64),
													 9, 4, 0});
	animation_manager_.AddAnimation(AnimationType::kWalkRight, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 704, 576, 64),
													 9, 4, 0});
	animation_manager_.AddAnimation(AnimationType::kWalkUp, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 512, 576, 64), 9,
													 4, 1});

  }
  FitWeaponSpriteOnAttack();
}

void PlayerView::CreateAttackAnimation() {
  const auto kSize = static_cast<int>(ItemType::kSize) - 1;

  for (int i = 0; i < kSize; ++i) {
	const auto kItemType = ItemType(i);
	if (kItemType == ItemType::kOneHandedSword) continue;
	auto &sprite = items_sprites_.at(kItemType);
	auto &sheet = items_icon_.at(kItemType);

	animation_manager_.AddAnimation(AnimationType::kSlashAttackUp, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 768, 384, 64), 6});
	animation_manager_.AddAnimation(AnimationType::kSlashAttackLeft, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 832, 384, 64), 6});
	animation_manager_.AddAnimation(AnimationType::kSlashAttackDown, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 896, 384, 64), 6});
	animation_manager_.AddAnimation(AnimationType::kSlashAttackRight, sprite, sheet,
									AnimationDetails{sf::IntRect(0, 960, 384, 64), 6});
  }
}

void PlayerView::OnMove(Direction direction) {
  if (player_state_ == PlayerState::kAttack)
	FitWeaponSpriteOnWalk();

  switch (direction) {
	case Direction::kDown:
	  animation_manager_.PlayAnimation(AnimationType::kWalkDown);
	  break;
	case Direction::kUp:
	  animation_manager_.PlayAnimation(AnimationType::kWalkUp);
	  break;
	case Direction::kLeft:
	  animation_manager_.PlayAnimation(AnimationType::kWalkLeft);
	  break;
	case Direction::kRight:
	  animation_manager_.PlayAnimation(AnimationType::kWalkRight);
	  break;
  }
  direction_ = direction;
  player_state_ = PlayerState::kWalk;
}

void PlayerView::OnAttack() {
  if (!equipped_items_.at(ItemType::kOneHandedSword)) return;

  if (player_state_ != PlayerState::kAttack)
	FitWeaponSpriteOnAttack();

  switch (direction_) {
	case Direction::kDown:
	  animation_manager_.PlayAnimation(AnimationType::kSlashAttackDown);
	  break;
	case Direction::kUp:
	  animation_manager_.PlayAnimation(AnimationType::kSlashAttackUp);
	  break;
	case Direction::kLeft:
	  animation_manager_.PlayAnimation(AnimationType::kSlashAttackLeft);
	  break;
	case Direction::kRight:
	  animation_manager_.PlayAnimation(AnimationType::kSlashAttackRight);
	  break;
  }

  player_state_ = PlayerState::kAttack;
}

void PlayerView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite_);
  for (const auto &[item, equipped]: equipped_items_) {
	if (equipped && item != ItemType::kOneHandedSword)
	  target.draw(items_sprites_.at(item));
  }

  if (equipped_items_.at(ItemType::kOneHandedSword))
	target.draw(items_sprites_.at(ItemType::kOneHandedSword));
}

void PlayerView::FitWeaponSpriteOnAttack() {
  auto &weapon_sprite = items_sprites_.at(ItemType::kOneHandedSword);
  weapon_sprite.move(-33.f, 17.f);
}

void PlayerView::FitWeaponSpriteOnWalk() {
  auto &weapon_sprite = items_sprites_.at(ItemType::kOneHandedSword);
  weapon_sprite.move(33.f, -17.f);
}

void PlayerView::Move(const sf::Vector2f &offset) {
  sprite_.move(offset);
  for (auto &[first, second]: items_sprites_)
	second.move(offset);
}

void PlayerView::SetPosition(const sf::Vector2f &new_position) {
  sprite_.setPosition(new_position);
  for (auto &[first, second]: items_sprites_)
	second.setPosition(new_position);
}

void PlayerView::OnEquipItem(const std::shared_ptr<Item> &item) {
  auto icon_path = item->GetIconPath();
  const auto kItemType = item->GetItemType();

  const auto it = icon_path.find(".png");
  if (it == std::string::npos)
	throw std::invalid_argument{"PlayerView::OnItemEquip -> invalid icon path" + icon_path};

  icon_path.insert(it, "_sheet");
  items_icon_.at(kItemType).loadFromFile("../resources/graphics/items_sheets/" + icon_path);
  items_sprites_.at(kItemType).setTexture(items_icon_.at(kItemType));
  equipped_items_.at(kItemType) = true;
}

void PlayerView::OnTakeOffItem(const std::shared_ptr<Item> &item) {
  const auto kItemType = item->GetItemType();
  OnTakeOffItem(kItemType);
}

void PlayerView::OnTakeOffItem(ItemType item_type) {
  equipped_items_.at(item_type) = false;
}

void PlayerView::OnUsedItem(const std::shared_ptr<IConsumable> &item) {

}

void PlayerView::PlayAnimation(AnimationType animation_type, bool force) {
  if (force) {
	animation_manager_.PlayAnimation(animation_type);
	return;
  }
  next_animation = animation_type;
}








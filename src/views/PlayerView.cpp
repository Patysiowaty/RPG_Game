#include "PlayerView.hpp"

PlayerView::PlayerView() {
  for (int i = 0; i < static_cast<int>(ItemType::kSize); ++i) {
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
  sf::Transformable::setPosition(x, y);
  sprite_.setPosition(x, y);
  for (auto &[first, second]: items_sprites_)
	second.setPosition(x, y);
  FitEquipment();
}

void PlayerView::Update(float delta_time) {
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

  auto &slash_weapon_anim = items_sprites_.at(ItemType::kOneHandedSword);
  auto &slash_weapon_sheet = items_icon_.at(ItemType::kOneHandedSword);

  animation_manager_.AddAnimation(AnimationType::kSlashAttackDown, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 256, 768, 128}, 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackLeft, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 128, 768, 128}, 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackUp, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 0, 768, 128}, 6});
  animation_manager_.AddAnimation(AnimationType::kSlashAttackRight, slash_weapon_anim, slash_weapon_sheet,
								  AnimationDetails{sf::IntRect{0, 384, 768, 128}, 6});
}

void PlayerView::OnMoveUp(const sf::Vector2f &offset) {
  sprite_.move(offset);
  for (auto &[first, second]: items_sprites_)
	second.move(offset);
  direction_ = Direction::kUp;
  animation_manager_.PlayAnimation(AnimationType::kWalkUp);
}

void PlayerView::OnMoveDown(const sf::Vector2f &offset) {
  sprite_.move(offset);
  for (auto &[first, second]: items_sprites_)
	second.move(offset);
  direction_ = Direction::kDown;
  animation_manager_.PlayAnimation(AnimationType::kWalkDown);
}

void PlayerView::OnMoveLeft(const sf::Vector2f &offset) {
  sprite_.move(offset);
  for (auto &[first, second]: items_sprites_)
	second.move(offset);
  direction_ = Direction::kLeft;
  animation_manager_.PlayAnimation(AnimationType::kWalkLeft);
}

void PlayerView::OnMoveRight(const sf::Vector2f &offset) {
  sprite_.move(offset);
  for (auto &[first, second]: items_sprites_)
	second.move(offset);

  direction_ = Direction::kRight;
  animation_manager_.PlayAnimation(AnimationType::kWalkRight);
}

void PlayerView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite_);
  for (const auto &[item, equipped]: equipped_items_)
	if (equipped)
	  target.draw(items_sprites_.at(item));
}

void PlayerView::OnAttack() {
  if (!equipped_items_.at(ItemType::kOneHandedSword)) return;
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
}

void PlayerView::OnItemEquip(ItemType item_type, std::string icon_path) {
  const auto it = icon_path.find(".png");
  if (it == std::string::npos) throw std::invalid_argument{"PlayerView::OnItemEquip -> invalid icon path" + icon_path};

  icon_path.insert(it, "_sheet");

  items_icon_.at(item_type).loadFromFile("../resources/graphics/items_sheets/" + icon_path);
}

void PlayerView::OnItemTakeOff(ItemType item_type) {
  equipped_items_.at(item_type) = false;
}

void PlayerView::FitEquipment() {
  for (auto&[item_type, item_sprite]: items_sprites_) {
	if (item_type == ItemType::kOneHandedSword)
	  item_sprite.move(-33.f, -37.f);
	else
	  item_sprite.move(0, 0);
  }
}




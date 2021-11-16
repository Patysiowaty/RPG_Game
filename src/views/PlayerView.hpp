#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../enums/Direction.hpp"
#include "../controllers/AnimationManager.hpp"
#include "../interfaces/IUpdatable.hpp"
#include "../enums/ItemType.hpp"
#include "../interfaces/IItemHandler.hpp"

enum class PlayerState {
  kNone, kWalk, kAttack
};

class PlayerView : public sf::Drawable, public IUpdatable, public IItemHandler {
 public:
  PlayerView();
  void CreateSprite(const std::string &texture_path);
  void SetPosition(float x, float y);
  void SetPosition(const sf::Vector2f &new_position);
  void Move(const sf::Vector2f &offset);

  void Update(float delta_time) override;

  void PlayAnimation(AnimationType animation_type, bool force = false);

  void OnMove(Direction direction);
  void OnAttack();
  void OnEquipItem(const std::shared_ptr<Item> &item) override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override;
  void OnTakeOffItem(ItemType item_type);
  void OnUsedItem(const std::shared_ptr<IConsumable> &item) override;

  bool HasActiveAnimation() const { return animation_manager_.GetCurrentAnimation() != AnimationType::kNone; }

 private:
  void CreateAnimations();
  void CreateWeaponAnimation();
  void CreateWalkAnimation();
  void CreateAttackAnimation();
  void FitWeaponSpriteOnAttack();
  void FitWeaponSpriteOnWalk();
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  PlayerState player_state_{PlayerState::kNone};
  sf::Sprite sprite_;
  sf::Texture player_icon_;
  std::map<ItemType, sf::Texture> items_icon_;
  std::map<ItemType, sf::Sprite> items_sprites_;
  std::map<ItemType, bool> equipped_items_;
  AnimationManager animation_manager_;
  Direction direction_{Direction::kDown};

  AnimationType next_animation{AnimationType::kNone};
};

#endif //PLAYERVIEW_HPP

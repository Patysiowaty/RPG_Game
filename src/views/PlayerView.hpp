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

class PlayerView : sf::Transformable, public sf::Drawable, public IUpdatable {
 public:
  PlayerView();
  void CreateSprite(const std::string &texture_path);
  void SetPosition(float x, float y);

  void Update(float delta_time) override;

  void OnMoveUp(const sf::Vector2f &offset);
  void OnMoveDown(const sf::Vector2f &offset);
  void OnMoveLeft(const sf::Vector2f &offset);
  void OnMoveRight(const sf::Vector2f &offset);
  void OnItemEquip(ItemType item_type, std::string icon_path);
  void OnItemTakeOff(ItemType item_type);
  void OnAttack();
  bool HasActiveAnimation() const { return animation_manager_.GetCurrentAnimation() != AnimationType::kNone; }

 private:
  void CreateAnimations();
  void FitEquipment();
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  sf::Sprite sprite_;
  sf::Texture player_icon_;
  sf::Texture sabre_sheet_;
  sf::Sprite sabre_sprite_;
  std::map<ItemType, sf::Texture> items_icon_;
  std::map<ItemType, sf::Sprite> items_sprites_;
  std::map<ItemType, bool> equipped_items_;
  AnimationManager animation_manager_;
  Direction direction_{Direction::kDown};
};

#endif //PLAYERVIEW_HPP

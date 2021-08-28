#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../enums/Direction.hpp"
#include "../controllers/AnimationsController.hpp"
#include "../interfaces/IUpdatable.hpp"

class PlayerView : sf::Transformable, public sf::Drawable, public IUpdatable {
 public:
  PlayerView() = default;
  explicit PlayerView(const std::string &texture_path);

  void CreateSprite(const std::string &texture_path);
  void SetPosition(float x, float y);

  void Update(float delta_time) override;

  void MoveUp(const sf::Vector2f &offset);
  void MoveDown(const sf::Vector2f &offset);
  void MoveLeft(const sf::Vector2f &offset);
  void MoveRight(const sf::Vector2f &offset);

 private:
  void CreateAnimations();
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  sf::Sprite sprite_;
  sf::Texture texture_;
  AnimationsController animation_controller_;
};

#endif //PLAYERVIEW_HPP

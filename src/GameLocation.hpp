#ifndef GAMELOCATION_HPP
#define GAMELOCATION_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "interfaces/IPlayerHandler.hpp"
#include "interfaces/IUpdatable.hpp"
#include "interfaces/IjsonSerializable.hpp"
#include "Collider.hpp"
#include <map>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <list>
#include <utility>
#include <SFML/Graphics/Sprite.hpp>

class LocationEntrance : sf::Transformable {
 public:

 private:

};

class GameLocation : public sf::Drawable, public IUpdatable, public IPlayerHandler {
 public:
  GameLocation() = default;

  GameLocation(const std::string &map_path, std::string map_name) : name_{std::move(map_name)} {
	LoadMapTexture(map_path);
  }

  void SetName(const std::string &name) {
	name_ = name;
  }

  void LoadMapTexture(const std::string &map_path) {
	texture_.loadFromFile(map_path);
	sprite_.setTexture(texture_);
  }

  void Update(float delta_time) override {

  }

  void OnPlayerMove(const sf::Vector2<float> &offset) override {
	sprite_.move(offset);
  }

 protected:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
	states.transform *= sprite_.getTransform();
	target.draw(sprite_, states);
  }

 private:
  std::string name_;
  sf::Sprite sprite_;
  sf::Texture texture_;
  std::list<LocationEntrance> entrances_list_;
};

#endif //GAMELOCATION_HPP

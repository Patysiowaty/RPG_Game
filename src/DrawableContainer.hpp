#ifndef DRAWABLECONTAINER_HPP
#define DRAWABLECONTAINER_HPP

#include <map>
#include <cstdint>
#include <list>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class DrawableContainer {
 public:
  void Draw(sf::RenderWindow &window) const;
  void AddDrawable(std::int32_t index, sf::Drawable *drawable);

 private:
  std::map<std::int32_t, std::list<sf::Drawable *>> indexed_drawable_list_;
};

#endif //DRAWABLECONTAINER_HPP

#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP
#include "../interfaces/IjsonSerializable.hpp"

struct GameConfig : public IJSONSerializable, public IJSONDeserializable {
  boost::property_tree::ptree Serialize() const override {
	boost::property_tree::ptree ptree;

	return ptree;
  }

  void Deserialize(const boost::property_tree::ptree &ptree) override {
	{
	  const auto &video_config = ptree.get_child("video");
	  window_title_ = video_config.get<std::string>("windowTitle");
	  window_icon_path_ = video_config.get<std::string>("windowIconPath");
	  window_size_.x = video_config.get<sf::Uint32>("windowSize.width");
	  window_size_.y = video_config.get<sf::Uint32>("windowSize.height");
	  window_v_sync_ = video_config.get<bool>("vSync");
	  style_ = video_config.get<uint32_t>("windowStyle");
	  context_settings_.antialiasingLevel = video_config.get<sf::Uint32>("antiAliasingLevel");
	}
  }

  std::string window_title_;
  std::string window_icon_path_;
  sf::Vector2u window_size_;
  sf::ContextSettings context_settings_;
  uint32_t style_;
  bool window_v_sync_;
};
#endif //GAMECONFIG_HPP

#ifndef JSONSERIALIZER_HPP
#define JSONSERIALIZER_HPP

#include "interfaces/IjsonSerializable.hpp"

class JSONSerializer {
 public:
  void Serialize(IJSONSerializable &json_serializable, const std::string &file_path);
  std::string Serialize(const IJSONSerializable &json_serializable);
  void Deserialize(IJSONDeserializable &json_deserializable, const std::string &file_path);
  void Deserialize(IJSONDeserializable &json_deserializable, const std::string &file_path,
				   const std::string &property_path);
  boost::property_tree::ptree Load(const std::string &file_path);
};

#endif //JSONSERIALIZER_HPP

#ifndef JSONSERIALIZER_HPP
#define JSONSERIALIZER_HPP

#include "interfaces/IjsonSerializable.hpp"

class JSONSerializer {
 public:
  JSONSerializer() = default;

  void Serialize(IJSONSerializable &json_serializable, const std::string &file_path);
  std::string Serialize(const IJSONSerializable &json_serializable);
  void Deserialize(IJSONSerializable &json_serializable, const std::string &file_path);

};

#endif //JSONSERIALIZER_HPP

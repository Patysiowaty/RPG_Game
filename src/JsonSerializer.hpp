#ifndef JSONSERIALIZER_HPP
#define JSONSERIALIZER_HPP

#include "interfaces/IjsonSerializable.hpp"
class JSONSerializer {
 public:
  JSONSerializer() = default;

  void SerializeAndSave(IJSONSerializable *json_serializable, const std::string &file_path);
  void LoadAndDeserialize(IJSONSerializable *json_serializable, const std::string &file_path);

};

#endif //JSONSERIALIZER_HPP

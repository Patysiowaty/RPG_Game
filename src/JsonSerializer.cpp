#include "JsonSerializer.hpp"
#include <boost/property_tree/json_parser.hpp>

void JSONSerializer::Serialize(IJSONSerializable &json_serializable, const std::string &file_path) {
  auto ptree = json_serializable.Serialize();
  boost::property_tree::write_json(file_path, ptree);
}

void JSONSerializer::Deserialize(IJSONSerializable &json_serializable, const std::string &file_path) {
  boost::property_tree::ptree ptree;
  boost::property_tree::read_json(file_path, ptree);
  json_serializable.Deserialize(ptree);
}

std::string JSONSerializer::Serialize(const IJSONSerializable &json_serializable) {
  std::string temp;
  auto ptree = json_serializable.Serialize();

  boost::property_tree::json_parser::write_json(temp, ptree);

  return temp;
}

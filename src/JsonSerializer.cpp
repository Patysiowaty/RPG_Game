#include "JsonSerializer.hpp"
#include <boost/property_tree/json_parser.hpp>

void JSONSerializer::Serialize(IJSONSerializable &json_serializable, const std::string &file_path) {
  auto ptree = json_serializable.Serialize();
  boost::property_tree::write_json(file_path, ptree);
}

void JSONSerializer::Deserialize(IJSONDeserializable &json_deserializable, const std::string &file_path) {
  boost::property_tree::ptree ptree;
  boost::property_tree::read_json(file_path, ptree);
  json_deserializable.Deserialize(ptree);
}

void JSONSerializer::Deserialize(IJSONDeserializable &json_deserializable, const std::string &file_path,
								 const std::string &property_path) {
  boost::property_tree::ptree ptree;
  boost::property_tree::read_json(file_path, ptree);
  const auto &child_path = ptree.get_child(property_path);
  json_deserializable.Deserialize(child_path);
}

std::string JSONSerializer::Serialize(const IJSONSerializable &json_serializable) {
  std::string temp;
  auto ptree = json_serializable.Serialize();

  boost::property_tree::json_parser::write_json(temp, ptree);

  return temp;
}

boost::property_tree::ptree JSONSerializer::Load(const std::string &file_path) {
  boost::property_tree::ptree ptree;
  boost::property_tree::read_json(file_path, ptree);

  return ptree;
}


#ifndef IJSONSERIALIZABLE_HPP
#define IJSONSERIALIZABLE_HPP
#include <boost/property_tree/ptree.hpp>
#include <string>

class IJSONSerializable {
 public:
  virtual ~IJSONSerializable() = default;
  virtual boost::property_tree::ptree Serialize() const = 0;
  virtual void Deserialize(const boost::property_tree::ptree &ptree) = 0;
};

#endif //IJSONSERIALIZABLE_HPP

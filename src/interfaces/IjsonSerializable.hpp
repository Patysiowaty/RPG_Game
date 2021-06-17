#ifndef IJSONSERIALIZABLE_HPP
#define IJSONSERIALIZABLE_HPP
#include <boost/property_tree/ptree.hpp>

class IJSONSerializable {
 public:
  virtual boost::property_tree::ptree Serialize() = 0;
  virtual void Deserialize(const boost::property_tree::ptree &ptree) = 0;
};

#endif //IJSONSERIALIZABLE_HPP

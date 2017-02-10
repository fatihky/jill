#include <map>
#include <vector>
#include <string>
#include "roaring.hh"

#ifndef JILL_FIELD_HEADER_INCLUDED
#define JILL_FIELD_HEADER_INCLUDED

namespace jill {
namespace table {

class FieldBase {};

enum FieldType {
  TIMESTAMP,
  DIMENSION,
  BOOL,
  METRIC_INT,
  METRIC_FLOAT
};

template <FieldType, typename T>
class Field : FieldBase {
 private:
 	// name of the field
  std::string name;
  // vector of values stored in the field
  std::vector<T> vals;
  // multi value fields(ex: tags)
  std::vector< std::vector<T> > mvals;
  // dimensions(ex: gender, country etc...)
  std::map<T, Roaring *> dict_;
  // true/false store
  Roaring *roar_;
  // element count that stored in this field
  int count_;
  // type of the this field
  FieldType type_;

 public:
 	// public methods
  Field(std::string name);

  // add new data to the field
  void insert(T &val);

  // DIMENSION methods
  std::map<std::string, Roaring *> &dict();

  // BOOL methods
  // get roaring bitmap of the field
  Roaring *roar() {
  	if (type_ != BOOL)
  		throw std::runtime_error("can not get roaring bitmap of the non-bool fields");
    return roar_;
  }
};

} // namespace table
} // namespace jill

#endif

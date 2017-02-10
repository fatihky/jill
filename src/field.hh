/*
  Copyright (c) 2017 Fatih Kaya
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom
  the Software is furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/

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
  std::string name_;
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
  std::string &name() {
    return name_;
  }

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

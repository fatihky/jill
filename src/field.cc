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

#include "field.hh"

// using namespace jill::table;
using namespace std;

namespace jill {
namespace table {

////////////////////////////////////////////////////////
/////// constructor implementations
////////////////////////////////////////////////////////

template <>
Field<TIMESTAMP, int64_t>::Field(std::string name):
    type_(TIMESTAMP), name_(name) {
}

template <>
Field<DIMENSION, string>::Field(string name):
    type_(TIMESTAMP), name_(name) {
}

template <>
Field<BOOL, bool>::Field(string name):
    type_(BOOL), name_(name) {
  roar_ = new Roaring();
}

template <>
Field<METRIC_INT, int>::Field(string name):
    type_(TIMESTAMP), name_(name) {
}

template <>
Field<METRIC_FLOAT, float>::Field(string name):
    type_(TIMESTAMP), name_(name) {
}

////////////////////////////////////////////////////////
/////// insert implementations
////////////////////////////////////////////////////////

template<>
void Field<TIMESTAMP, int64_t>::insert(int64_t &val) {
  vals.push_back(val);

  count_++;
}

template<>
void Field<DIMENSION, string>::insert(string &val) {
  Roaring *roar;

  if (dict_.count(val) > 0) {
    roar = dict_[val];
  } else {
    roar = new Roaring();
    dict_[val] = roar;
  }
  roar->add(count_);

  count_++;
}

template<>
void Field<BOOL, bool>::insert(bool &val) {
  if (val) {
    roar_->add((uint32_t)count_);
  }

  count_++;
}

template<>
void Field<METRIC_FLOAT, float>::insert(float &val) {
  vals.push_back(val);

  count_++;
}

} // namespace table
} // namespace jill

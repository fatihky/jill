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

#ifndef JILL_TABLE_HEADER_INCLUDED
#define JILL_TABLE_HEADER_INCLUDED

namespace jill {
namespace table {

class Table {
 private:
  std::map<std::string, FieldBase*> fields;
 public:
  template <FieldType type, typename T>
  void addField(Field<type, T> *field) {
    if (fields.count(field->name()) > 0) {
      throw std::runtime_error("Trying to add already added field to the table");
    }
    fields[field->name()] = (FieldBase *)field;
  }
};

} // namespace table
} // namespace jill

#endif // JILL_TABLE_HEADER_INCLUDED

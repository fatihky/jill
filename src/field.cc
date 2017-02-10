#include "field.hh"

// using namespace jill::table;

namespace jill {
namespace table {

template <>
Field<TIMESTAMP, int64_t>::Field(std::string name):
  	type_(TIMESTAMP), name(name) {
}

} // namespace table
} // namespace jill

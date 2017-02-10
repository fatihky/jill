#include "field.hh"

namespace jill {
namespace table {

class Table {
  std::map<std::string, FieldBase*> fields;
};

} // namespace table
} // namespace jill

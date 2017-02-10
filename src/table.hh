#include "field.hh"

namespace jill {
namespace table {

class Table {
 private:
  std::map<std::string, FieldBase*> fields;
 public:
  template<FieldType type, typename ValueType>
  void addField(Field<type, ValueType> field);
};

} // namespace table
} // namespace jill

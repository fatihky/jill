#include "field.hh"

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

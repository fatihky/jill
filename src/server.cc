#include "table.hh"

using namespace jill::table;

int main(int argc, char *argv[]) {
	jill::table::Table table;
	jill::table::Field<jill::table::TIMESTAMP, int64_t> *timestamp = new jill::table::Field<jill::table::TIMESTAMP, int64_t>("timestamp");

	table.addField<TIMESTAMP, int64_t>(timestamp);

	return 0;
}

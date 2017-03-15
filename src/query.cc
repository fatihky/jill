#include "query.hh"

namespace jill {
namespace query {

void Query::addFilter(Filter filter) {
	filters.push_back(filter);
}

} // namespace query
} // namespace jill

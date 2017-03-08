#include "query.hh"

namespace jill {
namespace query {

void Query::addFilter(FilterBase filter) {
	filters.push_back(filter);
}

} // namespace query
} // namespace jill

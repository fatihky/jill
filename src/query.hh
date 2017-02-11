#include <string>
#include <vector>
#include "roaring.hh"

#ifndef JILL_QUERY_HEADER_INCLUDED
#define JILL_QUERY_HEADER_INCLUDED

using namespace std;

namespace jill {
namespace query {

class Filter {
 private:
 	string rval;
 	string lval;
 	string op;
};

class GroupBy {
	string field;
};

class Aggeration {};

class PostAggregation {};

class Query {
 private:
	// filters
	vector<Filter> filters;
	// groupings
	vector<GroupBy> groupings;
	// aggregations
	vector<Aggeration> aggregations;
	// post-aggregations
	vector<PostAggregation> postAggregations;
 public:
	Query() {}
	void addFilter(Filter filter);
};

} // namespace query
} // namespace jill

#endif

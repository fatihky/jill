#include <string>
#include <vector>
#include "roaring.hh"

#ifndef JILL_QUERY_HEADER_INCLUDED
#define JILL_QUERY_HEADER_INCLUDED

using namespace std;

namespace jill {
namespace query {

enum FilterType {
  EQUAL,
  NOT_EQUAL
};

class FilterBase {};

template <FilterType filterType>
class Filter : public FilterBase {
 private:
  string rval;
  FilterType type;
  string op;
};

class GroupBy {
	string field;
};

class Aggeration {};

class PostAggregation {};

// QUERY RESULTS

class GroupByResult {
	string key;
	Roaring *bm;
};

class QueryResult {
	private:
  Roaring *filterResult;
  GroupByResult groupByResult;
};

// / QUERY RESULTS

class Query {
 private:
	// filters
	vector<FilterBase> filters;
	// groupings
	vector<GroupBy> groupings;
	// aggregations
	vector<Aggeration> aggregations;
	// post-aggregations
	vector<PostAggregation> postAggregations;
	// query result
	QueryResult result;
 public:
	Query() {}
	void addFilter(FilterBase filter);
};

} // namespace query
} // namespace jill

#endif

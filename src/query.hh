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

class Filter {
 public:
  string field;
  string lval;
  FilterType op;

  Filter(string field_, string lval, FilterType op_):
    field(field_), lval(lval), op(op_) {}
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
	vector<Filter *> filters;
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
	void addFilter(Filter *filter);
};

} // namespace query
} // namespace jill

#endif

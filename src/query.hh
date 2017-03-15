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
 private:
  string rval;
  string lval;
  FilterType op;
 public:
  Filter(string rval_, string lval, FilterType op_):
    rval(rval_), lval(lval), op(op_) {}
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

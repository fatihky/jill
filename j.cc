// g++ j.cc -o j -L/usr/local/lib -lroaring
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <map>
#include "roaring.hh"

enum FieldType {
  TIMESTAMP,
  DIMENSION,
  BOOL,
  METRIC_INT,
  METRIC_FLOAT
};

class FieldBase {};

template <FieldType, typename T>
class Field : FieldBase {
 private:
  std::string name;
  std::vector<T> vals;
  std::vector< std::vector<T> > mvals;
  std::map<T, Roaring *> dict_;
  Roaring *roar_;
  int count_;
  FieldType type_;
 public:
  Field(std::string name);
  void insert(T &val);
  std::map<std::string, Roaring *> &dict();
  Roaring *roar() {
    return roar_;
  }
};

template <FieldType type, typename T>
Field<type, T>::Field(std::string name):
    type_(type), name(name) {
  switch (type) {
    case METRIC_INT:
    case METRIC_FLOAT: {
    } break;
    default:
      throw std::runtime_error("invalid field type for Field<>");
  }
}

template <>
Field<DIMENSION, std::string>::Field(std::string name):
    type_(DIMENSION), name(name) {
  // switch (type) {
  //   case DIMENSION: {
  //   } break;
  //   default:
  //     throw std::runtime_error("invalid field type for string");
  // }
}

template <>
Field<TIMESTAMP, int64_t>::Field(std::string name):
    type_(TIMESTAMP), name(name) {
  // switch (type) {
  //   case TIMESTAMP: {
  //   } break;
  //   default:
  //     throw std::runtime_error("invalid field type for int64");
  // }
}

template <>
Field<BOOL, bool>::Field(std::string name):
    type_(BOOL), name(name) {
  roar_ = new Roaring();
  // switch (type) {
  //   case BOOL: {
  //     roar_ = new Roaring();
  //   } break;
  //   default:
  //     throw std::runtime_error("invalid field type for bool");
  // }
}

template <FieldType type, typename T>
void Field<type, T>::insert(T &val) {
  switch (type_) {
    case TIMESTAMP:
    case METRIC_INT:
    case METRIC_FLOAT: {
      vals.push_back(val);
    } break;
    case DIMENSION: {
      Roaring *roar;
      if (dict_.count(val) > 0) {
        roar = dict_[val];
      } else {
        roar = new Roaring();
        dict_[val] = roar;
      }
      roar->add(count_);
    } break;
    default:
      throw std::runtime_error("can not insert val to field with unknown type");
  }

  count_++;
}

template<>
std::map<std::string, Roaring *> &Field<DIMENSION, std::string>::dict() {
  return dict_;
}

class DimensionField {
 public:
  Field<DIMENSION, std::string> *strdim;
  Field<BOOL, bool> *booldim;
  bool isBoolDim;
  DimensionField(Field<DIMENSION, std::string> *strdim_): strdim(strdim_), isBoolDim(false) {}
  DimensionField(Field<BOOL, bool> *booldim_): booldim(booldim_), isBoolDim(true) {}
};

class Query {
 private:
 public:
  Query();
  ~Query();
};

class GroupByResult {
 public:
  std::vector<std::string> key;
  Roaring roaring;
};

static void genGroups(std::vector<GroupByResult> &groups, std::vector<std::string> &groupByKeys, std::map<std::string, FieldBase*> &fields, GroupByResult gres_, int index) {
  bool genGroup = index == (groupByKeys.size() - 1);
  std::string key = groupByKeys[index];
  FieldBase *fieldRef = fields[key];
  Field<DIMENSION, std::string> *field = (Field<DIMENSION, std::string> *)fieldRef;
  std::map<std::string, Roaring *> &dict = field->dict();
  for (std::map<std::string, Roaring *>::iterator it = dict.begin(); it != dict.end(); it++) {
    GroupByResult gres = gres_;
    gres.key.push_back(it->first);

    if (genGroup) {
      groups.push_back(gres);
    } else {
      genGroups(groups, groupByKeys, fields, gres, index + 1);
    }
  }
}

std::vector<GroupByResult> genGroupByResult(std::vector<std::string> &groupByKeys, std::map<std::string, FieldBase*> &fields) {
  std::vector<GroupByResult> groups;
  genGroups(groups, groupByKeys, fields, GroupByResult(), 0);
  return groups;
}

/// global fields
Field<TIMESTAMP, int64_t> *timestamp;
Field<DIMENSION, std::string> *publisher;
Field<DIMENSION, std::string> *advertiser;
Field<DIMENSION, std::string> *gender;
Field<DIMENSION, std::string> *country;
Field<BOOL, bool> *click;
Field<METRIC_FLOAT, float> *price;

void insert(std::string advertiser_, std::string gender_, std::string country_) {
  advertiser->insert(advertiser_);
  gender->insert(gender_);
  country->insert(country_);
}

int main(int argc, char *argv[]) {
  timestamp = new Field<TIMESTAMP, int64_t>("timestamp");
  publisher = new Field<DIMENSION, std::string>("publisher");
  advertiser = new Field<DIMENSION, std::string>("advertiser");
  gender = new Field<DIMENSION, std::string>("gender");
  country = new Field<DIMENSION, std::string>("country");
  click = new Field<BOOL, bool>("click");
  price = new Field<METRIC_FLOAT, float>("price");

  std::map<std::string, FieldBase*> fields;

  fields["timestamp"] = (FieldBase*)timestamp;
  fields["publisher"] = (FieldBase*)publisher;
  fields["advertiser"] = (FieldBase*)advertiser;
  fields["gender"] = (FieldBase*)gender;
  fields["country"] = (FieldBase*)country;
  fields["click"] = (FieldBase*)click;
  fields["price"] = (FieldBase*)price;

  insert("google.com", "male", "UK");
  insert("yahoo.com", "female", "US");
  insert("google.com", "female", "US");

  // select count(*) from logs where click = 1 group by country,gender
  {
    // generate new bitmap of all elements. so we need segment wide count variable
    int count = 3;
    Roaring roar(roaring_bitmap_from_range(0, count, 1));

    //////////////////////////////////////////////////////////////////////
    /////////// FILTERING STATE //////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    // do bitwise AND with click = 1
    // roar.printf();
    roar &= click->roar();
    // roar.printf();

    //////////////////////////////////////////////////////////////////////
    /////////// GROUPING STATE ///////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    // generate groups for every group by term
    std::vector< GroupByResult > groups;
    std::vector<std::string> groupByKeys;
    groupByKeys.push_back("advertiser");
    groupByKeys.push_back("gender");
    groupByKeys.push_back("country");

    groups = genGroupByResult(groupByKeys, fields);

    for (std::vector< GroupByResult >::iterator it = groups.begin(); it != groups.end(); it++) {
      const GroupByResult &gres = *it;
      std::vector<std::string> key = gres.key;
      for (std::vector<std::string>::iterator it2 = key.begin(); it2 != key.end(); it2++) {
        std::cout << *it2;
        if (std::distance(it2, key.end()) != 1) {
          std::cout << ", ";
        }
      }
      std::cout << std::endl;
    }
  }

  return 0;
}



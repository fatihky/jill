/*
  Copyright (c) 2017 Fatih Kaya
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom
  the Software is furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/

// fatih kaya <1994274@gmail.com>
// license: mit

struct selectStatement {
  std::string field;
  std::string aggregationFunc;
};

/// her alan bunu anlayabilecegi sekle cevirmeli. ornegin
/// sayi saklayan bir alan degeri sayiya cevirirken
/// katar saklayan bir alan bunu sayi olarak birakir
struct whereStatement {
  string field;
  string op;
  string val;
};

class query {
  std::vector<selectStatement> selectStatements;
  std::vector<whereStatement> whereStatements;
};

template <typename T>
class field {
 private:
  std:: string name;
  std::vector<T> vals;
  // multi value
  std::vector<std::vector<T>> mvals;
  int count_;
  // dict uyumu
  std::map<T, Roaring> dict;
  int has_dict_;
  std::vector<std::string> supportedOps;
 public:
  int add(const T &val);
  int count() {
    return count_;
  }

  Roaring executeWhereStatement(const whereStatement &ws) {
    if (supportedOps.indexOf(ws.op) == -1) {
      return genEmptyBitmap(); // todo: return error
    }

    if (ws.op in [EQUAL, NOT_EQUAL]) {
      if (!has_dict_) {
        throw "dict is required";
      }
      return new Roaring(dict[ws.value], {
        reverse: ws.op == NOT_EQUAL
      });
    }

    throw "not supported op: " + ws.op;
  }
};

class table {
private:
  int rowCount;
  std::string name;
  std::map<std::string, field> fields;
public:
  void executeQuery(const query &q) {
    bm = new Roaring(rowCount);
    for (ws in query.whereStatements) {
      if (ws.type == WHERE_AND) {
        bm &= executeWhereStatement(ws);
      }
    }
  }

  Roaring executeWhereStatement(whereStatement &ws) {
    field f = fields[ws.field]
    return field.executeWhereStatement(ws)
  }
};

struct tabletype {
  int count; // record count
	std::vector<uint64_t> time;
	std::vector<int> responsetime;
	std::map<std::string, Roaring> browser;
	std::map<std::string, Roaring> page;
};

tabletype table;

// select count(*) from table
void q1() {
  return table.count;
}

// select avg(responsetime) from table
void q2() {
  int count = table.count;
  uint64_t sum = 0;
  for (int i = 0; i < count; i++) {
    /* code */
  }
}
// select count(*) from table where browser = 'chrome'
void q3() {}
// select count(*) from table where browser = 'chrome' or browser = 'safari'
void q4() {}
// select count(*) from table group by browser
void q5() {}
// select count(*) from table group by page,browser
void q6() {}

int main(int argc, char const *argv[]) {
  return 0;
}

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

#include "table.hh"

using namespace jill::table;
using namespace std;

int main(int argc, char *argv[]) {
  jill::table::Table table;
  jill::table::Field<jill::table::TIMESTAMP, int64_t> *timestamp = new jill::table::Field<jill::table::TIMESTAMP, int64_t>("timestamp");
  Field<DIMENSION, string> *country = new Field<DIMENSION, string>("country");
  Field<BOOL, bool> *isClick = new Field<BOOL, bool>("isClick");
  Field<METRIC_FLOAT, float> *price = new Field<METRIC_FLOAT, float>("price");

  table.addField<TIMESTAMP, int64_t>(timestamp);
  table.addField<DIMENSION, string>(country);
  table.addField<BOOL, bool>(isClick);
  table.addField<METRIC_FLOAT, float>(price);

  // insert values
  int64_t ts = 1;
  string countryTR = "turkey";
  bool isClickVal = false;
  float priceVal = 1.99;

  timestamp->insert(ts);
  country->insert(countryTR);
  isClick->insert(isClickVal);
  price->insert(priceVal);

  return 0;
}

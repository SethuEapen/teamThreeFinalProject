#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include "twitter.h"
#include "tests.h"
#include <map>
#include <iostream>

using namespace std;

TEST_CASE("adj list to connections test 1", "[weight=5]") {
  Twitter twit("testdata_1.txt");
  const map<int, vector<int> > answer = {{1, {2, 3}}, {2, {3, 4}}, {3, {2, 4, 5}}, {4, {5}}, {5, {4}}};
  // twit.printMap();
  REQUIRE(answer == twit.connections);
}
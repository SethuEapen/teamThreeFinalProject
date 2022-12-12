#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include "../src/twitter.h"
#include "tests.h"
#include <map>
#include <iostream>

using namespace std;

TEST_CASE("testing population of adjacency list", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt");
  // string answer = "{{1, {2, 3}}, {2, {3, 4}}, {3, {2, 4, 5}}, {4, {5}}, {5, {4}}}";
  // string pass = twit.printMapDebug();
  // REQUIRE(answer == pass);
  map<int, vector<int>> ans = {{1, {2, 3}}, {2, {3, 4}}, {3, {2, 4, 5}}, {4, {5}}, {5, {4}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt");

  map<int, int> answer = {{1, 4}, {2, 2}, {3, 2}, {4, 1}, {5, 2}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}
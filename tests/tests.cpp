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

TEST_CASE("testing population of adjacency list 1", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt");
 
  map<int, vector<int>> ans = {{1, {2, 3}}, {2, {3, 4}}, {3, {2, 4, 5}}, {4, {5}}, {5, {4}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 1", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt");

  map<int, int> answer = {{1, 4}, {2, 2}, {3, 2}, {4, 1}, {5, 2}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}

TEST_CASE("testing population of adjacency list 2", "[weight=5]") {
  Twitter twit("../tests/testdata_2.txt");
 
  map<int, vector<int>> ans = {{1, {2, 3, 7, 12}}, {2, {4, 5}}, {3, {5, 6}}, {4, {3}}, {5, {6}}, 
                              {7, {8}}, {8, {9, 10}}, {9, {11}}, {10, {11}}, {11, {6}}, {12, {13}}, {13, {6}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 2", "[weight=5]") {
  Twitter twit("../tests/testdata_2.txt");

  map<int, int> answer = {{1, 5}, {2, 4}, {3, 3}, {4, 4}, {5, 3}, {6, 1}, 
                          {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 3}, {12, 4}, {13, 4}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}

TEST_CASE("testing population of adjacency list 3", "[weight=5]") {
  Twitter twit("../tests/testdata_3.txt");
 
  map<int, vector<int>> ans = {{1, {2, 3, 4}}, {2, {4}}, {3, {4}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 3", "[weight=5]") {
  Twitter twit("../tests/testdata_3.txt");

  map<int, int> answer = {{1, 4}, {2, 3}, {3, 3}, {4, 1}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}

TEST_CASE("testing population of adjacency list 4", "[weight=5]") {
  Twitter twit("../tests/testdata_4.txt");
 
  map<int, vector<int>> ans = {{1, {2}}, {2, {3, 4}}, {3, {1}}, {4, {1, 5}}, {5, {4, 2}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 4", "[weight=5]") {
  Twitter twit("../tests/testdata_4.txt");

  map<int, int> answer = {{1, 1}, {2, 1}, {3, 2}, {4, 1}, {5, 2}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}

TEST_CASE("testing dijkstra 1", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt");
  std::map<int, int> ans = {{1, 0}, {2, 2}, {3,2}, {4, 3}, {5, 4}};

  map<int, int> p = twit.dijkstra(1, 5);
  REQUIRE(p == ans);
}

TEST_CASE("testing dijkstra 2", "[weight=5]") {
  Twitter twit("../tests/testdata_2.txt");
  std::map<int, int> ans = {{1, 0}, {2, 4}, {3,3}, {4, 8}, {5, 6}, {7, 4}, 
                            {8,8}, {9,12}, {10, 12}, {11, 15}, {12, 4}, {13, 8}};
  
  map<int, int> p = twit.dijkstra(1, 13);
  
  REQUIRE(p == ans);
}

TEST_CASE("testing dijkstra 3", "[weight=5]") {
  Twitter twit("../tests/testdata_3.txt");
  std::map<int, int> ans = {{1, 0}, {2, 3}, {3,3}};
  
  map<int, int> p = twit.dijkstra(1, 4);
  
  REQUIRE(p == ans);
}

TEST_CASE("testing dijkstra 4", "[weight=5]") {
  Twitter twit("../tests/testdata_4.txt");
  std::map<int, int> ans = {{1, 0}, {2, 1}, {3,3}, {4, 2}, {5, 4}};
  
  map<int, int> p = twit.dijkstra(1, 5);
  
  REQUIRE(p == ans);
}
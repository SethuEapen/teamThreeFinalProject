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
  Twitter twit("../tests/testdata_1.txt", 1);
 
  map<int, vector<int>> ans = {{1, {2, 3}}, {2, {3, 4}}, {3, {2, 4, 5}}, {4, {5}}, {5, {4}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 1", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt", 1);

  map<int, int> answer = {{1, 4}, {2, 2}, {3, 2}, {4, 1}, {5, 2}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}

TEST_CASE("testing population of adjacency list 2", "[weight=5]") {
  Twitter twit("../tests/testdata_2.txt", 1);
 
  map<int, vector<int>> ans = {{1, {2, 3, 7, 12}}, {2, {4, 5}}, {3, {5, 6}}, {4, {3}}, {5, {6}}, {6, {}}, 
                              {7, {8}}, {8, {9, 10}}, {9, {11}}, {10, {11}}, {11, {6}}, {12, {13}}, {13, {6}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 2", "[weight=5]") {
  Twitter twit("../tests/testdata_2.txt", 1);

  map<int, int> answer = {{1, 5}, {2, 4}, {3, 3}, {4, 4}, {5, 3}, {6, 1}, 
                          {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 3}, {12, 4}, {13, 4}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}

TEST_CASE("testing population of adjacency list 3", "[weight=5]") {
  Twitter twit("../tests/testdata_3.txt", 1);
 
  map<int, vector<int>> ans = {{1, {2, 3, 4}}, {2, {4}}, {3, {4}}, {4, {}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 3", "[weight=5]") {
  Twitter twit("../tests/testdata_3.txt", 1);

  map<int, int> answer = {{1, 4}, {2, 3}, {3, 3}, {4, 1}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
}

TEST_CASE("testing population of adjacency list 4", "[weight=5]") {
  Twitter twit("../tests/testdata_4.txt", 1);
 
  map<int, vector<int>> ans = {{1, {2}}, {2, {3, 4}}, {3, {1}}, {4, {1, 5}}, {5, {4, 2}}};
  map<int, vector<int>> p = twit.connections;
  REQUIRE(p == ans);
}

TEST_CASE("testing weighting 4", "[weight=5]") {
  Twitter twit("../tests/testdata_4.txt", 1);

  map<int, int> answer = {{1, 1}, {2, 1}, {3, 2}, {4, 1}, {5, 2}};
  map<int, int> pass = twit.weights;
  REQUIRE(pass == answer);
} 

TEST_CASE("testing bfs on large 1", "[weight=5]") {
  Twitter twit("../data/twitter_combined.txt", 113058991);

  REQUIRE(2968 == twit.connections.size());
}

TEST_CASE("testing dijkstra 1", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt", 1);
  std::map<int, int> dans = {{1, 0}, {2, 2}, {3, 2}, {4, 3}, {5, 4}};
  std::map<int, int> pans = {{1, -1}, {2, 1}, {3, 1}, {4, 3}, {5, 3}};
  REQUIRE(twit.dist == dans);
  REQUIRE(twit.prev == pans);
}

TEST_CASE("testing dijkstra 2", "[weight=5]") {
  Twitter twit("../tests/testdata_2.txt", 1);
  std::map<int, int> dans = {{1, 0}, {2, 4}, {3,3}, {4, 8}, {5, 6}, {6, 4}, {7, 4}, 
                            {8,8}, {9,12}, {10, 12}, {11, 15}, {12, 4}, {13, 8}};
  std::map<int, int> pans = {{1, -1}, {2, 1}, {3,1}, {4, 2}, {5, 3}, {6, 3}, {7, 1}, 
                            {8,7}, {9,8}, {10, 8}, {11, 10}, {12, 1}, {13, 12}};
  
  REQUIRE(dans == twit.dist);
  REQUIRE(pans == twit.prev);
}

TEST_CASE("testing dijkstra 3", "[weight=5]") {
  Twitter twit("../tests/testdata_3.txt", 1);
  std::map<int, int> dans = {{1, 0}, {2, 3}, {3,3}, {4, 1}};
  std::map<int, int> pans = {{1, -1}, {2, 1}, {3,1}, {4, 1}};
    
  REQUIRE(dans == twit.dist);
  REQUIRE(pans == twit.prev);
}

TEST_CASE("testing dijkstra 4", "[weight=5]") {
  Twitter twit("../tests/testdata_4.txt", 1);
  std::map<int, int> dans = {{1, 0}, {2, 1}, {3,3}, {4, 2}, {5, 4}};
  std::map<int, int> pans = {{1, -1}, {2, 1}, {3,2}, {4, 2}, {5, 4}};
  
  REQUIRE(dans == twit.dist);
  REQUIRE(pans == twit.prev);
}

TEST_CASE("testing tarjans 1", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt", 1);
  twit.tarjans();
  std::vector<std::vector<int>> tans = {{1}};
  bool temp = false;
  for (auto i : twit.sccs) {
        if (std::find(i.begin(), i.end(), 1) != i.end()) {
            temp = true;
        }
    }
  
  REQUIRE(temp);
}

TEST_CASE("testing tarjans 2", "[weight=5]") {
  Twitter twit("../tests/testdata_1.txt", 2);
  twit.tarjans();
  std::vector<std::vector<int>> tans = {{3, 2}};
  bool temp = false;
  for (auto i : twit.sccs) {
        if (std::find(i.begin(), i.end(), 2) != i.end()) {
            temp = true;
        }
    }
  
  REQUIRE(temp);
}

TEST_CASE("testing tarjans 3", "[weight=5]") {
  Twitter twit("../tests/testdata_2.txt", 1);
  twit.tarjans();
  REQUIRE(twit.sccs.size() == 13);
}
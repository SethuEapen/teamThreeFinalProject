#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

class Graph {
    public:
        int vertices;
        vector<list<int> > adjacency;

        Graph(int vertices);
        void addEdge(int v1, int v2);
        void BFS(int traverse);
};
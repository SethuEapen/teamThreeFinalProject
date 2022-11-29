#pragma once


#include "twitter.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

class Graph {
    
        int vertices;
        vector<list<int> > adjacency;
    public:
        Graph(int vertices);
        void addEdge(int v1, int v2);
        void BFS(int traverse);
};
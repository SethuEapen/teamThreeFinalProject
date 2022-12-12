#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <list>
#include <stack>
//#include <bits/stdc++.h>


class Twitter
{
    public:
        Twitter(std::string path, int myID);
        void printMap();
        std::string printMapDebug();
        std::string printWeights();
        std::map<int,std::vector<int> > connections;
        std::map<int, int> dist;
        std::map<int, int> prev;
        std::map<int, int> weights;
        int ID;
        void dijkstra(int start);
        std::stack<int> dijkstraHelper(int end);
        std::set<int> BFS(int myID);
        int minDist(std::map<int, int> distance, std::set<int> seen);
        int INT_MAX = 2147483647;

};
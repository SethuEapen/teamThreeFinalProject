#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <list>
//#include <bits/stdc++.h>


class Twitter
{
    public:
        Twitter(std::string path, int myID);
        void printMap();
        std::string printMapDebug();
        std::string printWeights();
        std::map<int,std::vector<int> > connections;
        std::map<int, int> weights;
        std::map<int, int> dijkstra(int start, int end);
        std::set<int> BFS(int myID);
        int minDist(std::map<int, int> distance, std::set<int> seen);

};
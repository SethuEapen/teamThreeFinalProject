#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <set>
// #include <bits/stdc++.h>


class Twitter
{
    public:
        Twitter(std::string path);
        void printMap();
        std::map<int,std::vector<int> > connections;
        std::map<int, int> weights;
        std::map<int, int> dijkstra(int start, int end);
        int minDist(std::map<int, int> distance, std::set<int> seen);
        std::string printMapDebug();

};
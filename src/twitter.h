#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <list>
#include <stack>
#include <algorithm>
//#include <bits/stdc++.h>


class Twitter
{
    public:
        //fucntions
        Twitter(std::string path, int myID);
        void printMap();
        std::string printMapDebug();
        std::string printWeights();
        void dijkstra(int start);
        std::stack<int> dijkstraHelper(int end);
        std::set<int> BFS(int myID);
        int minDist(std::map<int, int> distance, std::set<int> seen);
        void tarjansHelper(int u, std::stack<int>* st);
        void tarjans();



        //variables
        std::map<int,std::vector<int> > connections;
        std::map<int, int> dist;
        std::map<int, int> prev;
        std::map<int, int> weights;
        std::map<int, int> disc;
        std::map<int, int> low;
        std::map<int, bool> stackMember; 
        std::vector<std::vector<int> > sccs;
        int INT_MAX = 2147483647;
        int ID;

};
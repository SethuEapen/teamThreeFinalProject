#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>

class Twitter
{
    public:
        Twitter(std::string path);
        void printMap();
    private:
        std::map<int,std::vector<int>> connections;
};
#include "twitter.h"
#include <fstream>

Twitter::Twitter(std::string path) {
    std::ifstream infile(path);
    int start, end;
    int count = 0;
    while (infile >> start >> end) {
        //std::cout << start << " follows " << end << std::endl;
        count++;
        connections[start].push_back(end);
    }
}

void Twitter::printMap() {
    for (auto const& [key, val] : connections) {
        std::cout << key << " | ";
        for(int i : val) {
            std::cout << i << ", ";
        } 
        std::cout << std::endl;
    }
}
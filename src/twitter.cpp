#include "twitter.h"
#include <fstream>

Twitter::Twitter(std::string path) {
    std::ifstream infile(path);
    int start, end;
    int count = 0;
    int maxWeight = 0;
    while (infile >> start >> end) {
        //std::cout << start << " follows " << end << std::endl;
        count++;
        connections[start].push_back(end);
        if (weights.find(end) != weights.end()) {
            weights[end]++;
        } else {
            weights[end] = 1;
        }
        if (maxWeight < weights[end]) {
            maxWeight = weights[end];
        }
    }
    for (auto const i : weights) {
        weights[i.first] = maxWeight - i.second + 1;
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

// std::vector<int> Twitter::dijkstra(int start, int end) {

// }
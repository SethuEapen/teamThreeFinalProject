#include "twitter.h"
#include <fstream>

Twitter::Twitter(std::string path) {
    std::ifstream infile(path);
    int start, end;
    int maxWeight = 0;
    while (infile >> start >> end) {
        //std::cout << start << " follows " << end << std::endl;
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
    for (auto const i : connections) {
        if (weights.find(i.first) == weights.end()) {
            weights[i.first] = 0;
        }
    }
    for (auto const i : weights) {
        weights[i.first] = maxWeight - i.second + 1;
    }
    for (auto i : weights) {
        std::cout << " | " << i.first << ", " << i.second;
    }
    std::cout << std::endl;
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

std::string Twitter::printMapDebug() {
    std::string output = "";
    output += "{";
    for (auto const& [key, val] : connections) {
        output += "{";
        output += std::to_string(key);
        output += ", {";
        for(int i : val) {
            output += std::to_string(i);
            output += ", ";
        } 
        output += "}, ";
    }
    output += "}";
    return output;
}



std::map<int, int> Twitter::dijkstra(int start, int end) {
    std::map<int, int> dist; //distances from start
    //std::map<int, std::vector<int>> paths;
    std::map<int, int> prev; //has it been seen
    std::set<int> seen;
    for (auto i : connections) { //for each node
        dist[i.first] = INT_MAX; //distances are all intmax
        //paths[i.first].push_back(start);
        prev[i.first] = -1; //we have not seen any
        seen.insert(i.first);
    }
    if (dist.find(start) != dist.end()) {
        dist[start] = 0;
    } else {
        std::cout << "START DOES NOT EXIST" << std::endl;
        std::map<int, int> toReturn;
        return toReturn;
    }
    while (!seen.empty()) { //repeat as many times as there are nodes
        int min = minDist(dist, seen);//find minimum distance of non seen things in the minimuum array
        seen.erase(min);
        //std::cout << min << std::endl;
        prev[min] = true;
        for (int j : connections[min]) { //for each connection of the minimum
            if (seen.find(j) != seen.end()) {
                if(dist[min] + weights[j] < dist[j]) {
                    dist[j] = dist[min] + weights[j];
                    //paths[j].push_back(min);
                    prev[j] = min;
                }
            }
        }
    }
    return dist;
}

int Twitter::minDist(std::map<int, int> distance, std::set<int> seen) {
    int minimum = INT_MAX;
    int ind;
              
    for (auto i : distance) {
        if (seen.find(i.first) != seen.end() && distance[i.first] <= minimum) {
            minimum = distance[i.first];
            ind = i.first;
        }
    }
    return ind;
}
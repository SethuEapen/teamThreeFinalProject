#include "twitter.h"
#include <fstream>

Twitter::Twitter(std::string path, int myID) {
    ID = myID;
    //Read in the file
    std::ifstream infile(path);
    int start, end;
    int maxWeight = 0;

    while (infile >> start >> end) {
        connections[start].push_back(end);
        if (connections.find(end) == connections.end()) {
            connections[end].resize(0);
        }
        if (weights.find(end) != weights.end()) {
            weights[end]++;
        } else {
            weights[end] = 1;
        }
        if (maxWeight < weights[end]) {
            maxWeight = weights[end];
        }
    }
    //init weights to 0
    for (auto const i : connections) {
        if (weights.find(i.first) == weights.end()) {
            weights[i.first] = 0;
        }
    }
    //transform the weights to correct
    for (auto const i : weights) {
        weights[i.first] = maxWeight - i.second + 1;
    }

    
    //get rid of extranious data
    if (connections.find(myID) == connections.end()) {
        std::cout << "ENTERED ID NOT VALID" << std::endl;
        exit(0);
    }


    std::set<int> keep = BFS(myID);

    std::map<int,std::vector<int> > connectionsUpdated;
    
    for (auto i : connections) {
        if (keep.find(i.first) != keep.end()) {
            connectionsUpdated[i.first].resize(0);
            for (auto j : i.second) {
                if (keep.find(j) != keep.end()) {
                    connectionsUpdated[i.first].push_back(j);
                }
            }
        }
    }
    std::cout << "Initial size: " << connections.size() << " users" << std::endl;
    connections = connectionsUpdated;
    if (connections.size() == 1) {
        std::cout << "   You have selected a user with no followers\n   Program exiting\n   Please try again with different user (default 113058991)" << std::endl;
        exit(0);
    }
    std::cout << "Reduced size: " << connections.size() << " users" << std::endl;
    dijkstra(myID);
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

std::set<int> Twitter::BFS(int myID) {
    int temp = myID;
    std::map<int, int> visited;
    for(auto i : connections) {
        if (i.first == myID) {
            visited.insert(std::pair<int, int>(i.first, 0));
        } else {
            visited.insert(std::pair<int, int>(i.first, -1));
        }
    }
    std::set<int> nodes;
    std::list<int> queue;
    queue.push_back(myID);
    nodes.insert(myID);
    while(!queue.empty()) {
        temp = queue.front();
        nodes.insert(temp);
        queue.pop_front();
        if (visited[temp] < 2) {
            for(auto i : connections[temp]) {
                if (visited.at(i) == -1) {
                    visited.at(i) = visited[temp] + 1;
                    queue.push_back(i);
                }
            }
        }
    }
    return nodes;
} 

std::string Twitter::printWeights() {
    std::string output;
    output += "{";
    for (auto i : weights) {
        //output += "{" + i.first + ", " + i.second + "}";
    }
    output += "}";
    return output;
}

std::stack<int> Twitter::dijkstraHelper(int end) {
    std::stack<int> path;
    int curr = end;
    if (prev.find(curr) != prev.end() || curr == ID) {
        while (curr != -1) {
            path.push(curr);
            curr = prev[curr];
        }
    }
    return path;
}

void Twitter::dijkstra(int start) {
    std::set<int> seen;
    for (auto i : connections) { //for each node
        dist[i.first] = INT_MAX; //distances are all intmax
        prev[i.first] = -1; //we have not seen any
        seen.insert(i.first);
    }
    if (dist.find(start) != dist.end()) {
        dist[start] = 0;
    } else {
        std::cout << "START DOES NOT EXIST" << std::endl;
        return;
    }
    while (!seen.empty()) { //repeat as many times as there are nodes
        int min = minDist(dist, seen);//find minimum distance of non seen things in the minimuum array
        seen.erase(min);
        //prev[min] = true;
        for (int j : connections[min]) { //for each connection of the minimum
            if (seen.find(j) != seen.end()) {
                if(dist[min] + weights[j] < dist[j]) {
                    dist[j] = dist[min] + weights[j];
                    prev[j] = min;
                }
            }
        }
    }
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

void Twitter::tarjans() {
    std::stack<int>* st = new std::stack<int>();
    for (auto i : connections) {
        disc[i.first] = -1;
        low[i.first] = -1;
        stackMember[i.first] = false;
    }
    tarjansHelper(ID, st);

    for (auto i : sccs) {
        if (std::find(i.begin(), i.end(), ID) != i.end()) {
            for (auto j : i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
            std::cout << "Size of strongly connected componenet: " << i.size() << std::endl;
            if (i.size() == 1) {
                std::cout << "Unfortunate you have no freinds :(" << std::endl;
            }
        }
    }

}

void Twitter::tarjansHelper(int u, std::stack<int>* st) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;
    for(auto i : connections[u]) {
        int v = i; 
        if (disc[v] == -1) {
            tarjansHelper(v, st);
            low[u] = std::min(low[u], low[v]);
        }
        else if (stackMember[v] == true) {
            low[u] = std::min(low[u], disc[v]);
        }
    }
    int w = 0;
    if (low[u] == disc[u]) {
        std::vector<int> output;
        while (st->top() != u) {
            w = (int)st->top();
            //std::cout << w << " ";
            output.push_back(w);
            stackMember[w] = false;
            st->pop();
        }
        w = (int)st->top();
        //std::cout << w << std::endl;
        output.push_back(w);
        stackMember[w] = false;
        st->pop();
        sccs.push_back(output);
    }
}
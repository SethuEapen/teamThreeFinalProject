#include "twitter.h"
#include <fstream>

Twitter::Twitter(std::string path, int myID) { // constructor
    ID = myID;
    //Read in the file
    std::ifstream infile(path);
    int start, end;
    int maxWeight = 0;

    std::cout << "*\ncaluclating edge weights..." << std::endl;
    while (infile >> start >> end) { // format is follower -> following
        connections[start].push_back(end);
        if (connections.find(end) == connections.end()) {//correction for nodes with no followers so they exist in connections
            connections[end].resize(0);
        }
        if (weights.find(end) != weights.end()) {//set up weights
            weights[end]++;
        } else {
            weights[end] = 1;
        }
        if (maxWeight < weights[end]) {// update max
            maxWeight = weights[end];
        }
    }
    //init weights to 0
    for (auto i : connections) {
        if (weights.find(i.first) == weights.end()) {
            weights[i.first] = 0;
        }
    }
    //transform the weights to correct
    for (auto i : weights) {
        weights[i.first] = maxWeight - i.second + 1;
    }

    
    //get rid of extranious data
    if (connections.find(myID) == connections.end()) {
        std::cout << "ENTERED ID NOT VALID" << std::endl;
        exit(0);
    }

    std::cout << "*\nRunning BFS... \n*" << std::endl;

    std::cout << "Initial size: " << connections.size() << " users" << std::endl;

    if (connections.size() > 10000) {// if you need to run bfs becuase dataset is large

        std::set<int> keep = BFS(myID); // bfs from start

        std::map<int,std::vector<int> > connectionsUpdated;
        
        for (auto i : connections) {//populate connections updated with all the values from connections that are in the BFS
            if (keep.find(i.first) != keep.end()) {
                connectionsUpdated[i.first].resize(0);
                for (auto j : i.second) {
                    if (keep.find(j) != keep.end()) {
                        connectionsUpdated[i.first].push_back(j);
                    }
                }
            }
        }
        connections = connectionsUpdated;// update the conections array
    }
    if (connections.size() == 1) { //if no followers
        std::cout << "   You have selected a user with no followers\n   Program exiting\n   Please try again with different user (default 113058991)" << std::endl;
        exit(0);
    }
    std::cout << "Reduced size: " << connections.size() << " users" << std::endl;
    std::cout << "*\nRunning Dijkstra's" << std::endl;
    dijkstra(myID); // run dijksras to get path to each node
}

void Twitter::printMap() { //not used but prints out the adjacency list 
    for (auto const& key : connections) {
        std::cout << key.first << " | ";
        for(int i : key.second) {
            std::cout << i << ", ";
        } 
        std::cout << std::endl;
    }
}

std::string Twitter::printMapDebug() { //print map debug also not used but it returns a string of the map
    std::string output = "";
    output += "{";
    for (auto const& key : connections) {
        output += "{";
        output += std::to_string(key.first);
        output += ", {";
        for(int i : key.second) {
            output += std::to_string(i);
            output += ", ";
        } 
        output += "}, ";
    }
    output += "}";
    return output;
}

std::set<int> Twitter::BFS(int myID) { //bfs implementation
    int temp = myID;
    std::map<int, int> visited;
    for(auto i : connections) {
        if (i.first == myID) {//initialize the visisted array with -1 for everything except for ID
            visited.insert(std::pair<int, int>(i.first, 0));
        } else {
            visited.insert(std::pair<int, int>(i.first, -1));
        }
    }
    std::set<int> nodes;
    std::list<int> queue;
    queue.push_back(myID);//start with your node
    nodes.insert(myID);
    while(!queue.empty()) {//until queue is empty
        temp = queue.front();
        nodes.insert(temp);
        queue.pop_front();//get next one in the queue
        if (visited[temp] < 2) {//go two itterations on bfs from the root node to get new list
            for(auto i : connections[temp]) { //for each neighbor
                if (visited.at(i) == -1) { // add to the queue
                    visited.at(i) = visited[temp] + 1;
                    queue.push_back(i);
                }
            }
        }
    }
    return nodes;
} 

std::string Twitter::printWeights() { // for debugging not used in end
    std::string output;
    output += "{";
    for (auto i : weights) {
        //output += "{" + i.first + ", " + i.second + "}";
    }
    output += "}";
    return output;
}

std::stack<int> Twitter::dijkstraHelper(int end) {//is the interface that utilizes the arrays populated by the dijkstras algorithm
    std::stack<int> path;
    int curr = end;
    if (prev.find(curr) != prev.end() || curr == ID) { // if the end exists or it the same as our node
        while (curr != -1) {//if we arent at the ID
            path.push(curr);
            curr = prev[curr];//set curr to the previous node in the path
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
                    prev[j] = min;//path finding back to the last node
                }
            }
        }
    }
}

int Twitter::minDist(std::map<int, int> distance, std::set<int> seen) { //helper function for dijkstras
    int minimum = INT_MAX;
    int ind;
              
    for (auto i : distance) {//for each one
        if (seen.find(i.first) != seen.end() && distance[i.first] <= minimum) { //if it exists and it is less
            minimum = distance[i.first];
            ind = i.first;//update
        }
    }
    return ind;
}

void Twitter::tarjans() {//tarjans
    std::stack<int>* st = new std::stack<int>(); //stack for current list of nodes in working subree
    for (auto i : connections) {//for each node
        disc[i.first] = -1;//set a low and high as not set (-1)
        low[i.first] = -1;
        stackMember[i.first] = false; //also say that it is not in the stack
    }
    tarjansHelper(ID, st); //recurse tarjans

    for (auto i : sccs) { //for each component
        if (std::find(i.begin(), i.end(), ID) != i.end()) {//if you are in the componenet
            for (auto j : i) {//print out the scc
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

void Twitter::tarjansHelper(int u, std::stack<int>* st) {//this constructs the sccs
    static int time = 0; // static for synchronization
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;
    for(auto i : connections[u]) {//for each connection in the passed u
        int v = i; 
        if (disc[v] == -1) {//if traverse
            tarjansHelper(v, st); //recurse
            low[u] = std::min(low[u], low[v]);//update low if needed
        }
        else if (stackMember[v] == true) { // if it is in the stack
            low[u] = std::min(low[u], disc[v]); //update low
        }
    }
    int w = 0;
    if (low[u] == disc[u]) { //if they are the same
        std::vector<int> output;
        while (st->top() != u) { //while the stack is not at your ID
            w = (int)st->top();
            //std::cout << w << " ";
            output.push_back(w); //push back into the SCC
            stackMember[w] = false;
            st->pop();
        }
        w = (int)st->top();
        //std::cout << w << std::endl;
        output.push_back(w);//push back your ID
        stackMember[w] = false;
        st->pop();
        sccs.push_back(output);//push back this scc vector
    }
}
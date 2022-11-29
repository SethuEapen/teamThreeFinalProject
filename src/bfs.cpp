#include "bfs.hpp"

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjacency.resize(vertices);
}

void Graph::addEdge(int v1, int v2) {
    adjacency[v1].push_back(v2);
}
void Graph::BFS(int traverse) {
    std::string path = "../data/twitter_combined.txt";
    Twitter twitter(path);
    vector<bool> visited;
    visited.resize(vertices, false);
    list<int> queue;

    visited[traverse] = true;
    queue.push_back(traverse);

    while(!queue.empty()) {
        traverse = queue.front();
        cout << traverse << " ";
        queue.pop_front();

        for(auto i: adjacency[traverse]){
            if(!visited[i]) {
                visited[i] = true;
                queue.push_back(i);
            }
        }       
    }
}


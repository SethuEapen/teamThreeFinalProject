#include <iostream>
#include "twitter.h"
#include <string>

using namespace std;

int main() {
    bool running = true;
    std::string path = "../data/test_set_1.txt";
    int myID;
    std::cout << "Please enter your Twitter ID: ";
    std::cin >> myID;
    Twitter twitter(path, myID);
    //twitter.printMap();
    std::cout << twitter.printMapDebug() << std::endl;
    std::string command;
    while (running) {
        std::cout << "Please enter a command (help): ";
        std::cin >> command;
        if (command == "exit") {
            running = false;
        } else if (command == "help") {
            std::cout << "   help - list commands \n   exit - exits program \n   BFS - prints out all the people N elements away from you \n   Dijkstra - finds shortest path between two people" << std::endl;
        } else if (command == "Dijkstra") {
            std::map<int, int> results = twitter.dijkstra(2, 3);
            std::cout << "  [";
            for (auto i : results) {
                std::cout << " | " << i.first << ", " << i.second;
            }
            std::cout << "]";
        } else {
            std::cout << "   Not a valid command. Type help for a list of commands" << std::endl;
        }
    }

}
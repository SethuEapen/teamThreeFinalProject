#include <iostream>
#include "twitter.h"
#include <string>
#include "bfs.hpp"

using namespace std;

int main() {
    bool running = true;
    std::string path = "../data/twitter_combined.txt";
    Twitter twitter(path);
    //twitter.printMap();
    std::string command;
    while (running) {
        std::cout << "Please enter a command (help): ";
        std::cin >> command;
        if (command == "exit") {
            running = false;
        } else if (command == "help") {
            std::cout << "   help - list commands \n   exit - exits program \n   BFS - prints out all the people N elements away from you \n   Dijkstra - finds shortest path between two people" << std::endl;
        } else {
            std::cout << "   Not a valid command. Type help for a list of commands" << std::endl;
        }
    }

}
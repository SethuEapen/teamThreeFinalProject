#include <iostream>
#include "twitter.h"
#include <string>

using namespace std;

int main() {
    bool running = true;
    std::string path = "../data/twitter_combined.txt";
    int myID;
    std::cout << "Please enter your Twitter ID (default 113058991): ";
    std::cin >> myID;
    Twitter twitter(path, myID);
    

    std::cout << "*\n*\n*\nAvailable users\n*\n" << std::endl; 

    for (auto i : twitter.connections) {
        std::cout << i.first << " | ";
    }
    std::cout << std::endl;

    std::cout << "*\n*\n*\n*\n" << std::endl; 


    //twitter.printMap();
    //std::cout << twitter.printMapDebug() << std::endl;
    std::string command;
    while (running) {
        std::cout << "Please enter a command (help): ";
        std::cin >> command;
        if (command == "exit") {
            running = false;
        } else if (command == "help") {
            std::cout << "   help - list commands \n   exit - exits program \n   BFS - prints out all the people N elements away from you \n   Dijkstra - finds shortest path between two people" << std::endl;
        } else if (command == "Dijkstra") {
            
            int end;
            
            std::cout << "Enter your outside freind: ";

            std::cin >> end;

            std::stack<int> path = twitter.dijkstraHelper(end);

            std::cout << "   ";
            
            while(!path.empty()) {
                int w = path.top();
                std::cout << w << " -> ";
                path.pop();
            }

            std::cout << std::endl;

            // std::cout << "  [";
            // for (auto i : results) {
            //     std::cout << " | " << i.first << ", " << i.second;
            // }
            // std::cout << "]";
        } else {
            std::cout << "   Not a valid command. Type help for a list of commands" << std::endl;
        }
    }

}
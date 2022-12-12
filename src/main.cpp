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
    

    std::cout << "*\n*\nAvailable users\n*" << std::endl; 

    for (auto i : twitter.connections) {
        std::cout << i.first << " | ";
    }
    std::cout << std::endl;

    std::cout << "*\n*\n*" << std::endl; 


    //twitter.printMap();
    //std::cout << twitter.printMapDebug() << std::endl;
    std::string command;
    while (running) {
        std::cout << "Please enter a command (help): ";
        std::cin >> command;
        if (command == "exit") {
            running = false;
        } else if (command == "help") {
            std::cout << "   help - list commands" << std::endl;
            std::cout << "   users - list available users" << std::endl;
            std::cout << "   exit - exits program" << std::endl;
            std::cout << "   dijkstra - finds shortest path between you and another person" << std::endl;
            std::cout << "   tarjans - prints out the SCC you are in" << std::endl;
        } else if (command == "users") {

            std::cout << "*\n*\nAvailable users\n*" << std::endl; 

            for (auto i : twitter.connections) {
                std::cout << i.first << " | ";
            }
            std::cout << std::endl;

            std::cout << "*\n*\n*" << std::endl; 

        } else if (command == "dijkstra") {
            
            int end;
            
            std::cout << "Enter your outside freind: ";

            std::cin >> end;

            if (twitter.connections.find(end) != twitter.connections.end()) {

                std::stack<int> path = twitter.dijkstraHelper(end);

                std::cout << "   ";
                
                while(!path.empty()) {
                    if (path.size() > 1) {
                        int w = path.top();
                        std::cout << w << " -> ";
                        path.pop(); 
                    } else {
                        int w = path.top();
                        std::cout << w;
                        path.pop(); 
                    }
                }

                std::cout << std::endl;
            } else {
                std::cout << "The user that you selected does not exist in the available users" << std::endl;
                std::cout << "Please refer above or type \"users\" to print out the list of available users" << std::endl;
            }
        } else if (command == "tarjans") {
            std::cout << "Finding strongly connected component..." << std::endl;
            twitter.tarjans();
        } else {
            std::cout << "   Not a valid command. Type help for a list of commands" << std::endl;
        }
    }

}
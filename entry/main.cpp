#include <iostream>
#include "twitter.h"
#include <string>

using namespace std;

int main() {
    bool running = true;
    std::string path = "../data/twitter_combined.txt"; // If you would like to change the dataset, input path here
    int myID;
    std::cout << "Please enter your Twitter ID (default 113058991): ";
    std::cin >> myID;
    Twitter twitter(path, myID); //new twitter object with the dataset and your id passed in
    

    std::cout << "*\n*\nAvailable users\n*" << std::endl; 

    for (auto i : twitter.connections) { //printing out the available users that you can search for using algorithms
        std::cout << i.first << " | ";
    }
    std::cout << std::endl;

    std::cout << "*\n*\n*" << std::endl; 


    //twitter.printMap();
    //std::cout << twitter.printMapDebug() << std::endl;
    std::string command;
    while (running) { //loop to enter in commands
        std::cout << "Please enter a command (help): ";
        std::cin >> command;
        if (command == "exit") { // if you ask to exit exit the loop
            running = false;
        } else if (command == "help") { // print dialog if help is entered
            std::cout << "   help - list commands" << std::endl;
            std::cout << "   users - list available users" << std::endl;
            std::cout << "   exit - exits program" << std::endl;
            std::cout << "   dijkstra - finds shortest path between you and another person" << std::endl;
            std::cout << "   tarjans - prints out the SCC you are in" << std::endl;
        } else if (command == "users") { // prints users available to the program

            std::cout << "*\n*\nAvailable users\n*" << std::endl; 

            for (auto i : twitter.connections) { //prints users
                std::cout << i.first << " | ";
            }
            std::cout << std::endl;

            std::cout << "*\n*\n*" << std::endl; 

        } else if (command == "dijkstra") { // uses helper function to get path between your user and other user
            
            int end;
            
            std::cout << "Enter your outside freind: ";

            std::cin >> end;

            if (twitter.connections.find(end) != twitter.connections.end()) { // if the entered freind exits

                std::stack<int> path = twitter.dijkstraHelper(end);

                std::cout << "   ";
                
                if (path.size() != 1 || end == myID) {
                    while(!path.empty()) { // print out the path
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
                } else { //if it doesnt exist
                    std::cout << "The friend that you requested is not connnected to you" << std::endl;
                }
            } else {
                std::cout << "The user that you selected does not exist in the available users" << std::endl;
                std::cout << "Please refer above or type \"users\" to print out the list of available users" << std::endl;
            }
        } else if (command == "tarjans") { // if entered tarjans
            std::cout << "Finding strongly connected component..." << std::endl;
            twitter.tarjans(); // run the function, prints are done in this function
        } else { // if entered a non-existing command
            std::cout << "   Not a valid command. Type help for a list of commands" << std::endl;
        }
    }

}
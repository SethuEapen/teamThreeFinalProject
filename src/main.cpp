#include <iostream>
#include "twitter.h"
#include <string>

using namespace std;

int main() {
    std::string path = "../data/twitter_combined.txt";
    Twitter twitter(path);
    twitter.printMap();
}
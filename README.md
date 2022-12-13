# teamThreeFinalProject
### teamThree's Final Project for cs225



**Github Organization**  
The build folder has our Makefile and all of the build files that we used to run CMake in order to compile and test our code.  

The data folder has sample datasets that we created to test our code. We made these since the dataset we originally use has thousands of values, so it was easier for us to use smaller sets to run our code.  

The src folder has all of our code files, including the main file. Twitter.cpp is the only file we needed to create for this project. We wrote all of our traversals/algorithms into it (BFS, Tarjan's, Dijkstra's), as well as the constructor and helper functions that we needed to implement the algorithms and run/test our code.  

The tests folder has our test files that we created to run our code.

***
**Running Instructions**
1) clone the repository onto your local machine
2) open the project in your IDE of choice (Running in the 225 environment is preferred as that will guarantee access to CMake)
3) you need to use CMake to build your own makefile. To do this, first enter the proper directory, then run the following in the terminal of the IDE you chose:  
    -- `mkdir build`  
    -- `cd build`  
    -- `cmake ..`
4) to run the test files, run:  
    -- `./test`
5) every time you need to recompile and test the code, you will need to run:  
    -- `make`  
    -- `./test`
6) to run the main file, run (after ensuring you're still in the build directory):  
    -- `./main`
7) every time you need to recompile and run the main file, you will need to run:  
    -- `make`  
    -- `./main`
    if you would like to change the dataset being used, go to entry/main.cpp and change the string path to whichever dataset you would like to use(extra datasets in tests directory)

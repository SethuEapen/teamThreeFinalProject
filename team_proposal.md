## Leading Question 
We want to figure out a better way to meet new people through social media. Right now social media is used to keep in touch with people you have met in person, but we think that if there was a better way to discover connections between people, we could better use the power of the internet. 

## Dataset Acquisition
## Data Format
The data originally comes in the form of 5 different files that all represent different things (circles, edges, egofeat, feat, featnames). However, this data lucky comes in a combined text file form that just has the edges. There are 88234 of these nodes. We will store all the nodes that these edges reference first as a set then match these edges to the nodes after in our graph data structure outlined below. 

## Data Correction
For the nodes that do not have any associated connections we can discard because they will take up data and not add to any possible clusters we can find. In the edge data, we will also have to discard any edges that reference non-existent nodes as they could cause null pointer issues when searching within the graph.

## Data Storage
For this project, we are using an adjacency list to help store our data. Using the dataset provided, we are going to take all the nodes in the combined text file and parse through it. From there, we are going to create an adjacency list in which each node will have a list of their connections. The data storage estimate cost of O(n^2).




## Algorithm 

##Function Inputs
We will take in a graph of all of the connected people which will be built out within the tokenization section. Dijkstra's algorithm requires weights, which we will extrapolate by saying the people with more total connections will have higher weights.

##Function Outputs: 
We will output a list of people who would work well together in an event. This will be the largest cycle in the graph of people that falls within the maximum size constraint provided. By definition of a cycle we know that every person there will know at least two others, and thus the party will be as the kids say “poppin”



##Function Efficiency: 
Based on research we did about Dijkstra's algorithm, the algorithm has an efficiency of O(ElogN) where E is the number of edges and N is the number of nodes. This is because a min heap is used to store the connected nodes and each node can be connected to n-1 nodes. Based on our research, the second algorithm we are using, the Eulerian path finding algorithm, will have a different efficiency based on the strategy we use to find the paths. For example, using the Fleury's algorithm the efficiency is O(|E|2) and if we use the Hierholzer's algorithm, the efficiency will be almost linear at O(E)



## Timeline
We are going to split up the work into 4 parts: tokenization/data Ingestion, BFS, eulerian path, and dijkstras
We can do all of these projects in parallel, so we will split up that work for the first week and rough out everything. In week two we should try to finalize the ingestion pipeline and maybe bfs if we can. Week three we can finish bfs for sure and after that we will work on the final two algorithms in pairs. On the last week, we can debug, and from there develop test cases and run them to ensure that our code accurately passes edge cases.





#Sources:

https://en.wikipedia.org/wiki/Eulerian_path
https://stackoverflow.com/questions/26547816/understanding-time-complexity-calculation-for-dijkstra-algorithm



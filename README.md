# graph_algos
c++ program that implements graph algorithms to find the shortest path.

This program takes in user input, this input is the starting node, the end node, the height and width of the graph, output(if they want output updated after every move, every few moves, or just the final graph, and if they want this to be saved to a file.) and if the edges are weighted. All the Algorithms work on both weighted and unweighted. Lastly, the user can choose to add walls, which are holes in the graph which none of the algorithms can pass. 

algorithms involved:

Dijkstra: The main algorithm in the program works by processing nodes with the shortest distance of the unprocessed nodes until it processes the final node, in which we stop, as we have found the shortest distance. The algorithm guarantees the shortest distance. 

A*: Modified Dijkstra, this algorithm adds a heuristic to the algorithms, with the purpose of ensuring that we are mostly processing nodes in the direction of our finish node, rather then just checking which node currently has the shortest distance, and does this by add the nodes current heuristic to its total distance to penalize nodes farther away from the finish node. This heuristic is typically an estimate, but due to the implementation of the graph, these estimates are exact.  This algorithm guarantees the path found is the shortest.

Greedy best first search: This algorithm uses only the heuristic mentioned in A* to find a path. It processes nodes by the one with the shortest heuristic to the finish node, which leads to a path found with very little checking but is not guaranteed to find the shortest path. This algorithm also handles duplicates, which is not an issue in the above algorithms, by assuming that if a node is in the vector to be processed, then the connecting node that added it to that vector list is the shortest heuristic path to it. This is done to prevent situations with walls where a path loops back on itself to a node that is waiting to be processed, so rather than continuing the looped path, we ignore it. This is the case as well for breadth search and depth search algorithms mentioned below.

breadth search: This algorithm works by processing on the nodes on the current level, before moving on to the next level. This can be both inefficient and be unable to find the shortest path since no checks for distance or heuristic are taken into consideration for the algorithm. So while this algorithm will find a path, there is no guarantee that the path is the shortest. 

depth first search: This algorithm works by processing a node and expanding it if applicable, if any of its child nodes can be expanded, then do so. The process continues until there are no child nodes to expand, which it then works its way back up, expanding other child nodes that have been skipped and their children and so on, or we find the finish node. This is by no means optimal and does not guarantee the shortest path as like breadth search there is no attempt and considering the distances or hurstics, it is only concerned with finding a path.


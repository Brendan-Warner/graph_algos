#pragma once
#include<vector>

struct grid
{
	int col;
	int row;
	char type = 'p';//p is for path in general, s is for shortest path nodes, v is for visited nodes, may change to s later, z is for start node, x is for end node, w is for wall node.
	int isVisited = 0;
	int distance = 1000000;//this is the main companent of dj's alg, and is used to sort its vectors
	int upEdge = 1;
	int downEdge = 1;
	int leftEdge = 1;
	int rightEdge = 1;
	int estimated_distance = 0;//this is the estimated distance used by A*, normaly the estimate is just that, but in the program the estimate ends up being an exeact, which still works for the alg
	int total_distance = 1000000;//this is used for sorting in A*, and is the edge distances used to get to this node + the estimated distance of this node from the finish.
	grid* up;
	grid* down;
	grid* left;
	grid* right;
	grid* prev;


};

void set_walls(vector<int>& wall_points);

bool is_wall(int i, int j, vector<int>& wall_points);

void create_grid(vector<grid*>& gridVec, int height, int width, int starth, int startc, int finishh, int finishc, char waited);

void create_grid(vector<grid*>& gridVec, int height, int width, int starth, int startc, int finishh, int finishc, vector<int>& wall_points, char waited);

void getNeighbors(grid* gridNode, vector<grid*>& neighborVect, vector<int>& neighborsEdges);

void getNeighbors(grid* current_node, vector<grid*> next_node);

void getNeighborsDepth(grid* current_node, vector<grid*> next_node);

void updateNeighbors(grid* gridNode);//for greedy alg, it calls an overloaded version of this.

void output_grid(vector<grid*>& gridvec, int height, int width, bool outputFile);


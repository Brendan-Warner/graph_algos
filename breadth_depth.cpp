using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include "gridFunc.h"
#include "breadth_depth.h"







void shortest_path_breadth_depth(grid* node, bool output_file)
{

	if (node->prev != nullptr)
	{
		shortest_path_breadth_depth(node->prev, output_file);
	}

	if (output_file)
	{

		ofstream userFile("OutputGrid.txt", ios::app);
		userFile << "[" << node->row << " " << node->col << "] edge distance " << node->distance << " total distance " << node->total_distance << " ";
		userFile.close();
	}


	cout << "[" << node->row << " " << node->col << "] edge distance " << node->distance << " total distance " << node->total_distance << " ";


	if (node->type == 'v')
	{
		node->type = 's';
	}

}

//this works by checking the huristic only, which in this case is estimated distance we first get the clossest, sort the vector, which on the first run does nothing, pop it from the vector, then gets its neighbors,
//we do this over and over until we get to the end node. this path is not certain to be optimal but thats a fault of the algorith itself. in a situation were we visited all avalible node and we still arn't at the end,  then
//we have no valide shortest path.
void breadth_depth_alg(int starth, int startc, int finishh, int finishc, int height, int width, int output, char walls, char waited, bool output_file, int alg)
{


	if (starth == finishh && startc == finishc)
	{
		cout << "Start and end are in the same spot, shortest path is 0" << endl;
		return;
	}
	vector<grid*> grid_v;
	int show = 0;


	//this is the vector that keeps track of the overall grid, doesn't change in size, and is used to output the current grid.


	//if the user wants walls, then we go to the set wall function.
	if (walls == 'y')
	{
		//every 2 numbers are the row and column of a wall
		vector<int> wall_points;
		set_walls(wall_points);

		//after we are done, we create the grid and pass the vector of wall point to add wall when we create the grid.
		create_grid(grid_v, height, width, starth, startc, finishh, finishc, wall_points, waited);


	}

	//if we are not creating walls in our grid, then we just call create grid without the wall vector.
	else {


		create_grid(grid_v, height, width, starth, startc, finishh, finishc, waited);
	}

	//visited grid vector is for keeping track of what grids we have processed.
	vector<grid*> visited_grid_v;

	int i = 0;
	grid* clossest;
	for (i = 0; i < grid_v.size(); i++)
	{
		if (grid_v[i]->row == starth && grid_v[i]->col == startc)
		{
			clossest = grid_v[i];
		}
	}

	vector<grid*> next_node;

	next_node.push_back(clossest);



	while (next_node.size())
	{


		clossest = next_node[0];



		next_node.erase(next_node.begin());








		if (clossest->type == 'w')
		{
			continue;
		}

		//call getneighbors function from gridfunctions but an overloaded one that only takes in a node and next_node that returns and upadated vecotr and updates their previous pointer to the node that set it as its neghbor
		//we need to check in that function that their isn't already that node in the next_node vector, we can do this by simply running through the vector checking for duplicates,
		if (alg == 4)
		{
			getNeighbors(clossest, next_node);
		}
		else
		{
			getNeighborsDepth(clossest, next_node);
		}



		clossest->isVisited = 1;
		visited_grid_v.push_back(clossest);

		if (clossest->type == 'p')
		{
			clossest->type = 'v';
		}

		if (clossest->estimated_distance == 0)
		{
			shortest_path_breadth_depth(clossest, output_file);

			if (output_file)
			{
				ofstream user_file("OutputGrid.txt", ios::app);
				user_file << endl;
				user_file.close();


			}


			cout << endl;



			output_grid(grid_v, height, width, output_file);
			return;
		}

		show++;


		if (show == output && output > 0)
		{


			output_grid(grid_v, height, width, output_file);
			show = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(750));
		}



	}

	int u = 0;
	if (output_file)
	{
		ofstream user_file("OutputGrid.txt", ios::app);
		user_file << "Their is no shortest path, nodes visited are";

		for (u = 0; u < visited_grid_v.size(); u++)
		{
			user_file << "[" << visited_grid_v[u]->row << "," << visited_grid_v[u]->col << " ]";
		}
		user_file.close();

	}



	cout << "Their is no shortest path, nodes visited are ";

	for (u = 0; u < visited_grid_v.size(); u++)
	{
		cout << "[" << visited_grid_v[u]->row << "," << visited_grid_v[u]->col << " ]";
	}












}
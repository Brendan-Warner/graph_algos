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

//this alog puts both breadth and depth first search alroithms into one, since the functionality needed for them to work is more or less the same, with the differance
//being if we but the child nodes in the front of the vector or in the back, if depth first, then in the front, if not, then in the back, everything else is the 
//same.
void breadth_depth_alg(int starth, int startc, int finishh, int finishc, int height, int width, int output, char walls, char waited, bool output_file, int alg)
{


	if (starth == finishh && startc == finishc)
	{
		cout << "Start and end are in the same spot, shortest path is 0" << endl;
		return;
	}
	vector<grid*> grid_v;//this is the vector that keeps track of the overall grid, doesn't change in size, and is used to output the current grid.
	int show = 0;


	


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

	//a very hacky way to get the first clossest node, the reason we do this is because we don't store the start node anywhere, and the only effeciant way to 
	//two more overlaoded functions could have been made for this algo to be faster, but decided against it. In any case, the start node is needed and we can't
	//use any sorting since this alrgo doesn't take things like distance or anything else into consideration. 
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

		//call getneighbors function from gridfunctions but an overloaded one that only takes in a node and next_node that returns and upadated vector and updates their previous pointer to the node that set it as its neghbor
		//we need to check in that function that their isn't already that node in the next_node vector, we can do this by simply running through the vector checking for duplicates,
		if (alg == 4)
		{
			getNeighbors(clossest, next_node);//gets neighbors and checkis for duplacates, adding child nodes to the end of the vector.
		}
		else
		{
			getNeighborsDepth(clossest, next_node);//gets neighbors and checkis for duplacates, adding child nodes to the front of the vector.
		}



		clossest->isVisited = 1;
		visited_grid_v.push_back(clossest);

		if (clossest->type == 'p')
		{
			clossest->type = 'v';
		}

		if (clossest->estimated_distance == 0)//this tells us that we are on the finish node, so we can end.
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

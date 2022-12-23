using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include "gridFunc.h"
#include "aStar.h"





bool sortGrid(const grid* node1, const grid* node2)
{
	return node1->total_distance < node2->total_distance;
}



//simply outputs the shortest path, it does this recursivly, starting from the finish node, and outputs the start node first and keeps outputing until we return to the finish node.
void shortest_pathAstar(grid* gridNode, bool outputFile)
{

	if (gridNode->prev == nullptr)
	{
		cout << endl;
	}
	else
	{
		shortest_pathAstar(gridNode->prev, outputFile);
	}

	if (outputFile)
	{

		ofstream userFile("OutputGrid.txt", ios::app);
		userFile << "[" << gridNode->row << " " << gridNode->col << "] edge distance " << gridNode->distance << " total distance " << gridNode->total_distance << " ";
		userFile.close();
	}


	cout << "[" << gridNode->row << " " << gridNode->col << "] edge distance " << gridNode->distance << " total distance " << gridNode->total_distance << " ";




}

//this algorithim is dj but includes an extra number, estimated distance, to try and ensure that we only check potentially relevent node that at least move in the right direction rather then treating every node as the same.
void AStar(int starth, int startc, int finishh, int finishc, int height, int width, int output, char walls, char waited, bool outputFile)
{
	//if the user gives a start and end node at the same spot, exit.
	if (starth == finishh && startc == finishc)
	{
		cout << "Start and end are in the same spot, shortest path is 0" << endl;
		return;
	}
	int show = 0;//used to compare to output, when this is the same as output, we output the grid, unless output = 0



	vector<grid*> gridV;//the vector the keeps track of all of our current nodes, does not change until the end.

	//if the usere want to add walls, then we call the walls function to fill up our walls vector wich is then passed to the overloaded create grid function.
	if (walls == 'y')
	{
		//every 2 numbers are the row and column of a wall
		vector<int> wall_points;
		set_walls(wall_points);

		create_grid(gridV, height, width, starth, startc, finishh, finishc, wall_points, waited);


	}

	//if we have no walls, then we simply create the grid normally.
	else {

		create_grid(gridV, height, width, starth, startc, finishh, finishc, waited);
	}
	vector<grid*> visitedGridV;
	vector<grid*> unvisitedGridV = gridV;


	//our main  loop that end when we run out of unvisited nodes.
	while (unvisitedGridV.size())
	{
		//overloaded sort function so that way we can sort this vecotr of structs.
		std::sort(unvisitedGridV.begin(), unvisitedGridV.end(), sortGrid);
		grid* clossest = unvisitedGridV[0];
		unvisitedGridV.erase(unvisitedGridV.begin());

		//if we get a wall as clossest, then we just pop it and skip processesing it.
		if (clossest->type == 'w')
		{
			continue;
		}

		//we update the neighbors distance from the current node if applicable.
		updateNeighbors(clossest);
		clossest->isVisited = 1;

		//if the node was a non visited path node, then we change its type to reflect that it's been visited.
		if (clossest->type == 'p')
		{
			clossest->type = 'v';
		}

		//if we enconter this situation, then the user has boxed us in with wall of created some other type of situation where a shortest path is not possible. we output the nodes we have viisted and the grid, then return.
		if (clossest->distance == 1000000)
		{
			cout << "Their is no valid shortest path, here are the nodes visited" << endl;
			int i = 0;
			//maybe move this to its own thing
			
			ofstream userFile("OutputGrid.txt", ios::app);
			
			for (i = 0; i < visitedGridV.size(); i++)
			{
				cout << "[" << visitedGridV[i]->row << "," << visitedGridV[i]->col << "]" << endl;
				if (outputFile)
				{
					userFile << "[" << visitedGridV[i]->row << "," << visitedGridV[i]->col << "]" << endl;
				}
			}
			output_grid(gridV, height, width, outputFile);
			while (!gridV.empty()) delete gridV.back(), gridV.pop_back();
			if (outputFile)
			{
				userFile.close();
			}
			return;



		}

		visitedGridV.push_back(clossest);
		show++;


		//if we are processing the finish node, then we are done, we have found the shortest path, so now we output it and return.
		if (clossest->row == finishh && clossest->col == finishc)
		{

			shortest_pathAstar(clossest, outputFile);//overload this function to include file stuff, besically, their are two seperate functions, this one and then the same one passed a ofstream file type, we choose this by checking outputFile


			if (outputFile)
			{
				ofstream userFile("OutputGrid.txt", ios::app);
				userFile << endl;
				userFile.close();


			}


			cout << endl;



			output_grid(gridV, height, width, outputFile);

			//add clean up functions here
			while (!gridV.empty()) delete gridV.back(), gridV.pop_back();


			return;

		}

		if (show == output && output > 0)
		{


			output_grid(gridV, height, width, outputFile);
			show = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(750));

		}




	}



}

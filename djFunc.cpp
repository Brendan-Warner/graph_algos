using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "gridFunc.h"
#include "djFunc.h"
#include <algorithm>




bool sortGridDj(const grid* node1, const grid* node2)
{
	return node1->distance < node2->distance;
}


//function simply outputs the list of nodes recursivly outputing start to finish node, starting from the finish node.
void shortest_pathDj(grid* gridNode, bool outputFile)
{
	//if the prev is null, that means we are at the start node of the linked list, so we start outputing the content we want from the nodes.
	if (gridNode->prev == nullptr)
	{
		cout << endl;
	}
	//if prev is not null, that means their is a node before this one, so we need to travel to that one first.
	else
	{

		shortest_pathDj(gridNode->prev, outputFile);
	}


	//we now start outputing the content from the nodes, with this set up, we start outputing the start node, then the next node on the path until we get to the finsih node.
	if (outputFile)
	{

		ofstream userFile("OutputGrid.txt", ios::app);
		userFile << "[" << gridNode->row << " " << gridNode->col << "] " << gridNode->distance << " ";
		userFile.close();
	}


	cout << "[" << gridNode->row << " " << gridNode->col << "] " << gridNode->distance << " ";




}

//this is the first and main function, follows dj's alg using a sorted vector to keep track of the next node to be processed.
void djskersFunc(int starth, int startc, int finishh, int finishc, int height, int width, int output, char walls, char waited, bool outputFile)
{
	//if the user gave us a situation where the start and finish are the same, then just exit.
	if (starth == finishh && startc == finishc)
	{
		cout << "Start and end are in the same spot, shortest path is 0" << endl;
		return;
	}
	int show = 0;


	//this is the vector that keeps track of the overall grid, doesn't change in size, and is used to output the current grid.
	vector<grid*> gridV;

	//if the user wants walls, then we go to the set wall function.
	if (walls == 'y')
	{
		//every 2 numbers are the row and column of a wall
		vector<int> wall_points;
		set_walls(wall_points);

		//after we are done, we create the grid and pass the vector of wall point to add wall when we create the grid.
		create_grid(gridV, height, width, starth, startc, finishh, finishc, wall_points, waited);


	}

	//if we are not creating walls in our grid, then we just call create grid without the wall vector.
	else {


		create_grid(gridV, height, width, starth, startc, finishh, finishc, waited);
	}

	//visited grid vector is for keeping track of what grids we have processed.
	vector<grid*> visitedGridV;

	//unvisited grid is the main vecotr acted on and is used to tell us what we haven't porcessed yet and the next thing to process
	vector<grid*> unvisitedGridV = gridV;


	//this is the main loop, we loop until thier is no unprocessed nodes.
	while (unvisitedGridV.size())
	{
		//overloaded sort so that we can sort a vector of objects.
		std::sort(unvisitedGridV.begin(), unvisitedGridV.end(), sortGridDj);
		grid* clossest = unvisitedGridV[0];
		unvisitedGridV.erase(unvisitedGridV.begin());

		//if the clossest node is a wall, then we pop it from unvisited and skip it.
		if (clossest->type == 'w')
		{
			continue;
		}
		//this is for updateing the distance of the neighbors assuming its applicable.
		updateNeighbors(clossest);
		clossest->isVisited = 1;

		//this simple changes the 'type' of the node to reflect the fact we have visited it.
		if (clossest->type == 'p')
		{
			clossest->type = 'v';
		}

		//if we have this situation, then the user has boxed us in with walls, so their is no shortest path avalible to us, so we output the nodes we have visited and output the grid.
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
			if (outputFile)
			{
				userFile.close();
			}
			return;
			output_grid(gridV, height, width, outputFile);
			while (!gridV.empty()) delete gridV.back(), gridV.pop_back();
			



		}


		//simple add the current to to the visited nodes
		visitedGridV.push_back(clossest);
		show++;//update show, which is used to decide if we should output the grid on this move according to user wishes.






		//if clossest is the finish node, then we have processed the finish node and we are done with the algorithm.
		if (clossest->row == finishh && clossest->col == finishc)//prpbably overload the shortes path function
		{

			shortest_pathDj(clossest, outputFile);//overload this function to include file stuff, besically, their are two seperate functions, this one and then the same one passed a ofstream file type, we choose this by checking outputFile


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


		//if our show is equal to output, then display the grid.
		if (show == output && output > 0)
		{


			
			output_grid(gridV, height, width, outputFile);
			show = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		}




	}


}

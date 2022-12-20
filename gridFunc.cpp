using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include "gridFunc.h"
#include <algorithm>






//this is for getting the user inputs on wall positions.
void set_walls(vector<int>& wall_points)
{
	char user_input = 'y';
	int user_num1 = 0, user_num2 = 0;


	//the user inputs two numbers, each number indicates ether a row or column, every two numbers is a position in the grid. if the user inputs random numbers not in the grid, then the grid is unafected.
	while (user_input == 'y')
	{
		cout << "Please enter the row you would like to add a wall to" << endl;
		cin >> user_num1;
		cout << "please enter the col you would like to add a wall to" << endl;
		cin >> user_num2;
		wall_points.push_back(user_num1);
		wall_points.push_back(user_num2);

		cout << "would you like to add more walls?" << endl;
		cin >> user_input;



	}


}
//this is a functino called when we are in the create grid function, to check if the created node needs to be a wall.
bool is_wall(int i, int j, vector<int>& wall_points)
{
	int t = 0;

	//this checks every two numbers, since every two numbers in the vector are a spot in the grid
	for (t = 0; t < wall_points.size(); t += 2)
	{
		//if the first number doesnt match the row, then just skip this set of two numbers
		if (wall_points[t] != i)
		{
			continue;
		}
		//if the second number isn't equal to the column, then we skip these two numbers
		if (wall_points[t + 1] != j)
		{
			continue;
		}

		//if both passed, then we erase the two numbers from the vecotr and return true.
		wall_points.erase(wall_points.begin() + t);
		wall_points.erase(wall_points.begin() + t);
		return true;


	}

	//if we get here, then the node created is not supposed to be a wall.
	return false;
}


//this functino creates the grid without walls.
void create_grid(vector<grid*>& gridVec, int height, int width, int starth, int startc, int finishh, int finishc, char waited)
{
	int i = 1, j = 1, t = 0;
	int total = height * width;

	//this goes head and fills the vector up to total.
	for (t = 0; t < total; t++)
	{

		//we creat a new struct pointer, and fill it with standered information.
		grid* gride = new grid();
		gride->row = i;
		gride->col = j;

		gride->right = nullptr;
		gride->down = nullptr;
		gride->up = nullptr;
		gride->left = nullptr;

		//this is for the A* alg to estimate how far this node is from the finish node.
		gride->estimated_distance = abs((i + j) - (finishc + finishh));

		//if the user chose to have the edges be weighted, then this randomizes the edges not dependent on previously created nodes.
		if (waited == 'y')
		{
			srand(time(0) + (i + j));

			gride->downEdge = (rand() % 7) + 1;

			gride->rightEdge = (rand() % 7) + 1;
		}

		if (i > 1)
		{

			gridVec[t - width]->down = gride;//set the down pointer of the node above this one to the current node.

			gride->up = gridVec[t - width];//set current nodes up pointer to the node above it.
			gride->upEdge = gridVec[t - width]->downEdge;//set the upedge of the the current node equal to the down edge of the above node.

		}

		if (j > 1)
		{

			gride->left = gridVec[t - 1];//set the left edge of the node equal to the pointer to the node just left of it.
			gride->leftEdge = gridVec[t - 1]->rightEdge;//we set current nodes left edge wequal to the left nodes right edge
			gridVec[t - 1]->right = gride;//we node set the left nodes right pointer to the current node.
		}

		//if the current node is our start node, then we change its type and total distances to 0,
		if (i == starth && j == startc)
		{
			gride->type = 'z';
			gride->distance = 0;
			gride->total_distance = 0;
		}

		//if the current node is the end node, then we change its type
		if (i == finishh && j == finishc)
		{
			gride->type = 'x';
		}

		gridVec.push_back(gride);
		j++;

		//this is used to keep track of the current row we are on, when j becomes bigger then width, then we know that we have reached the end of a row. so reset j and incrment i
		if (j > width)
		{
			j = 1;
			i++;
		}



	}
}

//same as the above function except the check for walls is gone.
void create_grid(vector<grid*>& gridVec, int height, int width, int starth, int startc, int finishh, int finishc, vector<int>& wall_points, char waited)
{
	int i = 1, j = 1, t = 0;
	int total = height * width;
	bool check_wall = true;


	for (t = 0; t < total; t++)
	{


		grid* gride = new grid();
		gride->row = i;
		gride->col = j;

		gride->right = nullptr;
		gride->down = nullptr;
		gride->up = nullptr;
		gride->left = nullptr;
		gride->estimated_distance = abs((i + j) - (finishc + finishh));


		//we can only randomize the down and right edges since those are the only parts not dependent on something that is made before it, if the node is on the edge of the grid and doesn't have a top/ right node, then
		//these values won't be used, the left and up edges are to be destrmined by thier left and up neighbors assuming thats applicable.
		if (waited == 'y')
		{
			srand(time(0) + (i + j));

			gride->downEdge = (rand() % 7) + 1;//these edges are weights rather then actual distance, these can return zero, meaning that in the distance cals the distance between this and its down node is just one.

			gride->rightEdge = (rand() % 7) + 1;
		}

		if (i > 1)
		{

			gridVec[t - width]->down = gride;

			gride->up = gridVec[t - width];
			gride->upEdge = gridVec[t - width]->downEdge;

		}

		if (j > 1)
		{

			gride->left = gridVec[t - 1];
			gride->leftEdge = gridVec[t - 1]->rightEdge;
			gridVec[t - 1]->right = gride;
		}


		if (i == starth && j == startc)
		{
			gride->type = 'z';
			gride->distance = 0;
			gride->total_distance = 0;


		}

		if (i == finishh && j == finishc)
		{
			gride->type = 'x';
		}

		check_wall = is_wall(i, j, wall_points);

		if (check_wall && gride->type != 'x' && gride->type != 'z')
		{

			gride->type = 'w';
		}

		gridVec.push_back(gride);
		j++;


		if (j > width)
		{
			j = 1;
			i++;
		}



	}
}

//grab the neighbering nodes as well as their edges, only grab the neighbors is they haven't been visited yet and if the neighbor actually exists.
void getNeighbors(grid* gridNode, vector<grid*>& neighborVect, vector<int>& neighborsEdges)
{
	if (gridNode->left != nullptr && gridNode->left->isVisited == 0)
	{
		neighborVect.push_back(gridNode->left);
		neighborsEdges.push_back(gridNode->leftEdge);
	}

	if (gridNode->right != nullptr && gridNode->right->isVisited == 0)
	{
		neighborVect.push_back(gridNode->right);
		neighborsEdges.push_back(gridNode->rightEdge);
	}
	if (gridNode->up != nullptr && gridNode->up->isVisited == 0)
	{
		neighborVect.push_back(gridNode->up);
		neighborsEdges.push_back(gridNode->upEdge);
	}
	if (gridNode->down != nullptr && gridNode->down->isVisited == 0)
	{
		neighborVect.push_back(gridNode->down);
		neighborsEdges.push_back(gridNode->downEdge);
	}
}





//this fucntion updates the neighboring nodes distance assuming that distance is lower then its current one.
void updateNeighbors(grid* gridNode)
{
	vector<grid*> neighborsVect;
	vector<int> neighborsEdges;
	getNeighbors(gridNode, neighborsVect, neighborsEdges);// we pass the created neighbors vector and the current node to get neighbors function to grab unvisted neighbors of the node.
	int size = neighborsVect.size();
	int i = 0;

	for (i = 0; i < size; i++)
	{
		//if the neighbor being checked already has a distance and that distance is shorter then the new node checking it, we don't wnat to change its current distance nor its previous node to maintain the shortest path to this node.
		//A* and dj both use this to judge which node to consider previous, A* can use this since it only cares about the huristic when sortings, otherwise, its considers a shorter path as the one with the shortest distance only,
		//so we check for shorter distance then update the total distance with the huristice of the current node for sorting purposes, otherwise, the hurisitic doesn't matter.
		if (neighborsVect[i]->distance >= gridNode->distance + neighborsEdges[i])
		{
			neighborsVect[i]->distance = gridNode->distance + neighborsEdges[i];// we set the new distance to this node
			neighborsVect[i]->total_distance = neighborsVect[i]->distance + neighborsVect[i]->estimated_distance;//we set the new total distance to the node
			neighborsVect[i]->prev = gridNode;//set the current node as the new rpevious of this nieghbor.
		}
	}

	//not sure if this is necessary, but clean up the two vectors.
	neighborsVect.clear();
	neighborsEdges.clear();

}




//this is the check to ensure that we don't have a the node already in the vector, if we do, then we don't want to add it again and set its previous again, since in that kind of situation, we may be looping back 
//on ourselves, which if we didn't check would lead to a wierd loop path being considered our "shortest" path when it's not even close, this may be the inccorect way to implament the alg but this should lead to better path
//results.
bool in_vector(grid* neighbor_node, vector<grid*> next_node)
{
	int i = 0;

	for (i = 0; i < next_node.size(); i++)
	{
		if (neighbor_node == next_node[i])
		{
			return true;
		}
	}
	return false;

}


//this is for the gbfs alg, it updates the next_node vector which is where we store to be processed nodes, we also update the prev here, since if we have gotten to a spot once before, then that should be 
//the fastest path to it, their is howver, no certanty since we don't have anything to properly judge it since the alg soley uses huristics, from what testing i have done to mess with the idea, it seems like if we add
//a node to the vector, then the prev it has should be the shortest huristic path to it, and thus we need to make sure that when we have that node in the vector, we don't update its previous.
//this is also used by breadth depth search, since the object of breadth depth search is to check all the nodes at a level before moving on, this will give us all the nodes at a level when we do this, and since they are 
//added at the end, we don't acidently expand a node when we arn't ready and we do it in order, if their are two nodes at a level to check, we grad the first nodes children, then expand the second node and grad its children,
//then we expand the first nodes children, then expand the second nodes children, then we move to their children, ect. since their is no check for distance or hurisitc, this will undoutably produce some unoptimal paths,
//while the check for if a node is in the vector will cause the program to assume that while at least two node should be able to get to any single node, the node will have only one parent/path to it, and that the path is most
//effeciant, since their is no checks on distances and no requirment to ensure the path is the shortest, this should be fine. this just like gbfs use of this function, should keep paths that loop on themselves when they encounter walls
//from being formed, or at least make them less likly.
void getNeighbors(grid* current_node, vector<grid*> next_node)
{
	if (current_node->left != nullptr && current_node->left->isVisited == 0)
	{
		//we check to make sure that the node is not already in our vector, if it is, then a shorter path to it already exists. 
		if (!in_vector(current_node->left, next_node))
		{

			next_node.push_back(current_node->left);
			current_node->left->prev = current_node;
		}

	}

	if (current_node->right != nullptr && current_node->right->isVisited == 0)
	{
		if (!in_vector(current_node->right, next_node))
		{
			next_node.push_back(current_node->right);
			current_node->right->prev = current_node;
		}

	}
	if (current_node->up != nullptr && current_node->up->isVisited == 0)
	{
		if (!in_vector(current_node->up, next_node))
		{
			next_node.push_back(current_node->up);
			current_node->up->prev = current_node;
		}

	}
	if (current_node->down != nullptr && current_node->down->isVisited == 0)
	{
		if (!in_vector(current_node->down, next_node))
		{
			next_node.push_back(current_node->down);
			current_node->down->prev = current_node;
		}

	}
}

//this is for depth search alg, when we add a node to the vecotr, we add it to the beggining, gathering the next set of nodes, and expanding the first, not exactly how the algorith normaly owrks, as it uses a que, but the 
//outcome should still be the same, as we expand the first node we encounter and we continue exapanding the first node every time till we hit a end or we find our objective, due to the set up of the grid, not adding any 
//walls will lead us to eventually find a path off of the left node since thats added first, but it will more then likly be really bad or unoptimal, but the alg doesn't garentee a shortest path but simply finds a path since their is no distance or hursitice 
//involved. just like the above function for gbfs and breadth, the check for if the node already being in the vector should stop looping paths, and ensure we have consitant paths through the program. 
//the idea is that if we have the node in the vector with a depth search alg, then we already have a shorter/equal path, in the shorter case its the path has looped on itselft do to walls, and in the equal case 
//it shoudln't matter which one connects to it, so just take the first one. 
void getNeighborsDepth(grid* current_node, vector<grid*> next_node)
{
	//maybe add something to alter the distance here so the final output looks nicer
	if (current_node->left != nullptr && current_node->left->isVisited == 0)
	{
		//we check to make sure that the node is not already in our vector, if it is, then a shorter path to it already exists. 
		if (!in_vector(current_node->left, next_node))
		{

			next_node.insert(next_node.begin(), current_node->left);
			current_node->left->prev = current_node;
			current_node->left->distance = current_node->distance + 1;
		}

	}

	if (current_node->right != nullptr && current_node->right->isVisited == 0)
	{
		if (!in_vector(current_node->right, next_node))
		{
			next_node.insert(next_node.begin(), current_node->right);
			current_node->right->prev = current_node;
		}

	}
	if (current_node->up != nullptr && current_node->up->isVisited == 0)
	{
		if (!in_vector(current_node->up, next_node))
		{
			next_node.insert(next_node.begin(), current_node->up);
			current_node->up->prev = current_node;
		}

	}
	if (current_node->down != nullptr && current_node->down->isVisited == 0)
	{
		if (!in_vector(current_node->down, next_node))
		{
			next_node.insert(next_node.begin(), current_node->down);
			current_node->down->prev = current_node;
		}

	}
}



//this outputs the current situation of the grid.
void output_grid(vector<grid*>& gridvec, int height, int width, bool outputFile)
{
	int i = 0, j = 0, t = 0, y = 0;
	//system("clear");

	
	ofstream userFile("OutputGrid.txt", ios::app);
	

	//if the user want the grid outputed to file, then we do that.



		//this goes through the entire vector.
	for (t = 0; t < gridvec.size(); t++)
	{
		//this is to check for a non edge node of the grid, if it it, then we do this output.
		if (j < width - 1)
		{
			cout << gridvec[t]->type << "---" << gridvec[t]->rightEdge << "---";
			if (outputFile)
			{
				userFile << gridvec[t]->type << "---" << gridvec[t]->rightEdge << "---";
			}
			j++;
		}

		//if we are at the edge of the vecotr, then we need to ensure our output doesnt have an extra -- after it.
		else
		{
			if (outputFile)
			{
				userFile << gridvec[t]->type << endl;
			}
			cout << gridvec[t]->type << endl;
			j++;
			i++;


			//this is for outputing the down edges that aren't the last row.
			if (i < height)
			{
				//this outputs the first | between the node and its down edge value
				for (y = 0; y < j; y++)
				{
					cout << "|       ";
					if (outputFile)
					{
						userFile << "|       ";
					}
				}
				cout << endl;
				if (outputFile)
				{
					userFile << endl;
				}

				//we know we are at the end of a row, so we should just work backwards to get all of the down edge values
				for (y = (j - 1); y >= 0; y--)
				{
					cout << gridvec[t - y]->downEdge << "       ";
					if (outputFile)
					{
						userFile << gridvec[t - y]->downEdge << "       ";
					}
				}
				cout << endl;
				if (outputFile)
				{
					userFile << endl;
				}

				//outputs the second | connecting the edge value to the next node, !!!!!!!!!!!!!check if this height check is needed!!!!!!!!!!!
				if (i < height)
				{
					for (y = 0; y < j; y++)
					{
						cout << "|       ";
						if (outputFile)
						{
							userFile << "|       ";
						}
					}
					cout << endl;
					if (outputFile)
					{
						userFile << endl;
					}
				}


			}
			j = 0;

		}



	}

	if (outputFile)
	{
		userFile << endl;
		userFile.close();
	}


}


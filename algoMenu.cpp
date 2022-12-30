using namespace std;
#include <iostream>
#include <vector>
#include "algoMenu.h"
#include "gridFunc.h"
#include "djFunc.h"
#include "aStar.h"
#include "gbfs.h"
#include "breadth_depth.h"





//main function, asks the user everything from which alg they want to if they want to include walls and if the graph is weighted at all.
void menuFunc()
{
	int gridh = 0, gridw = 0, startrow = 0, startcol = 0, finishrow = 0, finishcol = 0, output = 0, algo_choice = 0;
	char walls = ' ', waited = ' ', choiceFile = ' ';
	bool outputFile = false;


	cout << "Hello, welcome to this algorithim visualization program" << endl;
	cout << "Here, you will select a start and stop node, as well as and walls, through the use of column and row posistions." << endl;
	cout << "You can choose not to place any walls" << endl;
	cout << "The visulaiszation number is for how many times the visuization will appear, selecting  zero will only have the final graph and the shortest path displayed, anything more then one will display a new graph every number of checks" << endl;
	cout << "to the number inputed." << endl;
	cout << "If you create a sistuation where it is immpossible to get the the finish posistion, then the final visulization will be of what was attempted with no shortest path displayed" << endl;




	cout << "Please enter a number for the height of your grid" << endl;
	cin >> gridh;
	cout << "Please enter a number for the width of your grid" << endl;
	cin >> gridw;
	cout << "Please enter the row of your starting posistion." << endl;
	cin >> startrow;
	cout << "Please enter the colum of your starting posisiton." << endl;
	cin >> startcol;
	cout << "Please enter the row of your finishing posistion" << endl;
	cin >> finishrow;
	cout << "Please enter the column of your finishing posisiton" << endl;
	cin >> finishcol;

	cout << "Please enter how much you would like to refresh the grid, putting in zero will have the grid only display the final result." << endl;
	cin >> output;
	cout << "Would you like to place any walls?" << endl;
	cin >> walls;

	cout << "Would you like your algorithm to be weighted?" << endl;
	cin >> waited;

	cout << "Would you like your output to go to a file?" << endl;
	cin >> choiceFile;

	if (choiceFile == 'y')
	{
		outputFile = true;
	}

	cout << "Which algorithm would you like to use? input 1 for djskers and 2 for A*" << endl;
	cin >> algo_choice;


	if (algo_choice == 1)
	{
		djskersFunc(startrow, startcol, finishrow, finishcol, gridh, gridw, output, walls, waited, outputFile);
	}

	else if (algo_choice == 2)
	{
		AStar(startrow, startcol, finishrow, finishcol, gridh, gridw, output, walls, waited, outputFile);
	}

	else if (algo_choice == 3)
	{
		GBFS_alg(startrow, startcol, finishrow, finishcol, gridh, gridw, output, walls, waited, outputFile);
	}

	else if (algo_choice >= 4)
	{
		breadth_depth_alg(startrow, startcol, finishrow, finishcol, gridh, gridw, output, walls, waited, outputFile, algo_choice);
	}




}


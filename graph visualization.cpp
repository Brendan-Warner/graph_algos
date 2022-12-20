using namespace std;
#include <iostream>
#include "algoMenu.h"
#include "gridFunc.h"
#include "djFunc.h"
#include "aStar.h"
#include "gbfs.h"


//include for the the functions of the menu and its options.
//include for the file that is just the algorithms and them going through the motions, may not need to do depending on implmentation of the menu and have the include for the algs in their




int main(int argc, char* argv[])
{
	bool again = true;
	char user_choice = ' ';


	//this starts the program and asks the user after their done if they would like to try it out again.
	//the could probably be move to the menu function
	while (again == true)
	{
		menuFunc();
		cout << "Would you like to use the program again? enter" << endl;
		cin >> user_choice;
		if (user_choice == 'n')
		{
			again = false;
		}
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

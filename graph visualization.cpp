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



//jordan vaughn

#include "GameOfLife2_csci2312.h"
#include <iostream>


using namespace csci2312;

int main() {
	int input;
	GameOfLife board;
	int rule;
		 //used in menu
	int choice;
	unsigned int seeds;
	const int FILE = 1, RANDOM = 2, QUIT = 3;
	
	//the menu
	do {
		
		//display menu
		std::cout << "Press 1 to seed the board from a file." << std::endl;
		std::cout << "Press 2 to manually enter the number of starting living cells." << std::endl;
		std::cout << "Press 3 to quit." << std::endl;
		std::cin >> choice;

		if (choice != 3) {
			std::cout << "How many iterations of the game of life do you want? ";
			std::cin >> input;

			//ask for which rule to execute
			std::cout << "Would you like to execute standard rules(press 1), or rule B2/S (press 2)?" << std::endl;
			cin >> rule;
			while (rule < 1 || rule > 2) {
				std::cout << "Try again for valid input." << std::endl;
				cin >> rule;
			}
		}

		//if manual is selected, promt user to enter number of seeds
		if (choice == 2) {
			std::cout << "Please enter the number of living seeds to start with: ";
			std::cin >> seeds;
		}


		while (choice<FILE || choice >QUIT)
		{
			std::cout << "please make a valid selection: ";
			std::cin >> choice;
		}

		switch (choice)
		{
		case FILE: board.seedBoard("gameSeed.txt");		//user could input string, but I'm just putting it in to save time running the program
			while (input > 0)	//use number of iterations, indicated by user
			{	
				board.run(rule);
				std::cout << board;
				--input;
				std::cout << "\n\n";
			}
			break;

		case RANDOM: board.seedBoard(seeds);
			while (input > 0)	//use number of iterations, indicated by user
			{
				board.run(rule);
				std::cout << board;
				--input;
				std::cout << "\n\n";
			}
			break;

		}

	} while (choice != 3);
	
}//end main
	



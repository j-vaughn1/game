#include "GameOfLife2_csci2312.h"
#include <string>
#include <fstream>//used for taking input from file to seed the game
#include <iostream>
#include <iomanip>
#include <stdlib.h>


namespace csci2312 {

	//####################################
		//Cell definitions
	csci2312::Cell::Cell() {
		state = 0;
	}

	//**********************
	csci2312::Cell::Cell(bool state) {
		face = state;
	}

	//**********************
	csci2312::Cell::~Cell() {//deletes all dynamically allocated memory

	}

	//*********************
	bool Cell::getState() const {
		return state;
	}

	//*******************
	void Cell::setState(bool newState) {
		state = newState;
		if (state == 0)
			face = dead;
		else
			face = alive;
	}

	char Cell::getFace() const {
		return face;
	}



	//########################################################################
		//Game class definitions

	GameOfLife::GameOfLife() throw (bad_alloc) {
		
	}

	//*****************************
	GameOfLife::GameOfLife(const GameOfLife& game) {		//copy constructor, makes deep copy
		GameOfLife newGame;

		newGame.currentLife = new CellPtr[30];	//dynamically allocate newGame's current life array
		for (int i = 0; i < 30;++i)
			newGame.currentLife[i] = new Cell[30];

		for (int i = 0; i < 30; i++)//make newGame's currentLife array equal to game
		{
			for (int j = 0; j < 30; j++)
			{
				newGame.currentLife[i][j].setState(game.currentLife[i][j].getState());
			}
		}
		
	}

	//***********************************
	csci2312::GameOfLife::~GameOfLife() {//destructor

		for (int i = 2; i < 28; i++)
		{

			delete[] nextLife[i];

		}

		for (int i = 2; i < 28; i++)
		{

			delete[] currentLife[i];

		}
	}

	//***********************************
	void GameOfLife::seedBoard(string fileName) throw (FileIOException) {//no combination of input methods seeded the game here, using getline and stoi, or even
		int input;								//putting all the int's on the same line separated by a space, or on their own line.
		std::ifstream infile;
		infile.open(fileName);


		currentLife = new CellPtr[30];
		for (int i = 0; i < 30;++i)
			currentLife[i] = new Cell[30];

		if (infile.fail())
		{
			std::cout << "The file failed to open, sorry." << std::endl;
			return;
		}
	
			for (int i = 0;i < 30;i++)
			{

				for (int j = 0; j < 30;j++)
				{
					infile >> input;
					
						currentLife[i][j].setState(input);
					
				}
			}

		
		infile.close();

	}

	//*************************
	void GameOfLife::seedBoard(size_t seeds) {
		//seeds is the number of living cells to be placed in the board
		//placed at random locations, use rand to get random indexes
		srand(time(NULL));

		currentLife = new CellPtr[30];
		for (int i = 0; i < 30;++i)
			currentLife[i] = new Cell[30];

		size_t count = 0;


		while (count < seeds)
		{
			int randNumber1 = rand() % (26)+2;
			int randNumber2 = rand() % (26)+2;
			count++;

			currentLife[randNumber1][randNumber2].setState(true);
		}

		
	}

	//***********************************
	ostream& operator << (ostream& out, const GameOfLife& board) {

		for (int i = 1; i < 28;i++)//print current life 
		{
			if (i > 1)//moves to new line
				std::cout << std::endl;

			for (int j = 1; j < 28; j++)//sends face to out
			{
				
					out << board.currentLife[i][j].getFace();
			}
		}

		return out;
	}

	//*************************
	void csci2312::GameOfLife::run(int rule) {

		nextLife = new CellPtr[30];//allocate next life

		for (int i = 0; i < 30; i++)
			nextLife[i] = new Cell[30];
			
			for (int i = 2; i < 28; i++)//make next life equal to current
			{
				for (int j = 2; j < 28; j++)
				{
					nextLife[i][j].setState(currentLife[i][j].getState());
				}
			}


			

			//rules of life, use nested life to check each index
			for (int i = 2; i < 28;i++)
			{
				for (int j = 2; j < 28; j++)
				{
					int neighborsAlive = 0;//keep track of living neighbors

					if (currentLife[i][j].getState() == false)  //if the cell is dead, check for living neighbors
					{
						if (currentLife[i - 1][j - 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i - 1][j].getState() == 1)
							neighborsAlive++;
						if (currentLife[i - 1][j + 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i][j - 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i][j + 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i + 1][j - 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i + 1][j].getState() == 1)
							neighborsAlive++;
						if (currentLife[i + 1][j + 1].getState() == 1)
							neighborsAlive++;
						
					}


					if (currentLife[i][j].getState() == true)     //if the cell is alive, check for overcrowding or loneliness     
					{
						if (currentLife[i - 1][j - 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i - 1][j].getState() == 1)
							neighborsAlive++;
						if (currentLife[i - 1][j + 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i][j - 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i][j + 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i + 1][j - 1].getState() == 1)
							neighborsAlive++;
						if (currentLife[i + 1][j].getState() == 1)
							neighborsAlive++;
						if (currentLife[i + 1][j + 1].getState() == 1)
							neighborsAlive++;
					
					}

					//rules
					
					if (rule == 1)	//normal rules
					{
						if (currentLife[i][j].getState() == false) {//for dead cells
							if (neighborsAlive == 3)
							{
								nextLife[i][j].setState(true);
							}
							else
								nextLife[i][j].setState(false);
							
						}

						if (currentLife[i][j].getState() == true) {//for living cells
							if (neighborsAlive < 2 || neighborsAlive >3)
								nextLife[i][j].setState(false);
							else
								nextLife[i][j].setState(true);
						}
					}

					if (rule == 2) {	//rule B2/S
						bool answer = false;
						answer = executeRuleB2_S(neighborsAlive, currentLife[i][j].getState());
				
						if (answer == true)
							nextLife[i][j].setState(true);
						else
							nextLife[i][j].setState(false);
					}
				}
			}
			
			
			for (int i = 2; i < 28; i++)//set current life equal to next life
			{
				for (int j = 2; j < 28; j++)
				{
					currentLife[i][j].setState(nextLife[i][j].getState());
				}
			}
			
			
			cin.get();
	}

	//*******************************************
	istream& operator >> (istream& in, const GameOfLife& board) {

		return in;
	}

	//****************************
	bool GameOfLife::executeRuleB2_S(unsigned int countAlive, bool currentState) {
		
		//rule B2/S causes a phoenix pattern. All living cells die, but come to life if they have 2 living neighbors

				if (currentState == false)  //if the cell is dead, check for living neighbors
				{

					if (countAlive == 2)
					{
						return true;
					}

				}

				if (currentState == true)     //if the cell is alive, check for overcrowding or loneliness     
				{
					
					return false;
				}
			
	
	}//end rule


}//end namespace















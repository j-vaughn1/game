// FILE GameOfLife2.h
// CLASSES: GamOfLife, Cell and FileIOException, all in the namespace csci2312.
//
// DESCRIPTION: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
// The universe of the Game of Life is an infinite two - dimensional orthogonal grid of square cells, 
// each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated"
// Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent.
// At each step in time, the following transitions occur:
//
// Any live cell with fewer than two live neighbours dies, as if caused by under-population.
// Any live cell with two or three live neighbours lives on to the next generation.
// Any live cell with more than three live neighbours dies, as if by over-population.
// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
// 
// The initial pattern constitutes the seed of the system. 
// The first generation is created by applying the above rules simultaneously to every cell in the seed: 
// - births and deaths occur simultaneously, and the discrete moment at which this happes is sometimes called a tick. 
// In other words, each generation is a pure function of the preceding one. The rules continue to be applied 
// repeatedly to create further generations. 
//    
//   
////////////////  GameOfLife /////////////////////////
// HIGH LEVEL DESIGN
// State the key points of your high level design: 
// - What are the GameOfLife (GOL) class' responsibilities?
//   GOL houses the Cells in a matrix. 
//   It sets and executes all the rules on the Cells (future idea: imagine this responsibility given to a Cell)
// - What are the responsibilities of a Cell?
//   A Cell knows and can articulate its state (even if it is dead :) 
// - What data structure(s) of cells will you use to model and implement the board?
//   This implementation will use static two-dimensional arrays
// - How will you go about keeping track of the current and next cell populations?
//   One array will hold the current state, and the second array will hold the calculated next generation state. 
//   After the current state is displayed, the next state will be copied over the current state for subsequent display
//   [ OPTIONAL STUDENT TASK: briefly describe another, perhaps more efficient, implementation idea ]
// - How will you go about game boundary conditions (edges and corners)?
//   [ STUDENT TASK:  fill in your implementation approach.  With "halo" approach, you will need a board of size MAX_BOARD+2]
// - How will you handle error conditions (when a method fails in any way)?
//   A method with a known risk of failure will return a success/fail (zero/one) status.  
//   Every calling layer will propagate the status code to the outer layer, and the most outer layer (the main) will exit
//   
// A PRECONDITION states what must be true when/before a function is invoked. 
// The responsibility to meet/check the pre-condition belongs with the calling layer.
// If that condition is not met, the behavior of the called function is not predictable and may result in failure
//
// A POSTCONDITION states what is the function outcome, and if/how the state of the object(s) has changed
//
// =================== PUBLIC CLASS API - Cell
// CONSTRUCTORS:
//     Cell();
//     POSTCONDITION: Creates a dark/dead Cell
// 
// MODIFIERS/MUTATORS:
//     void setState(bool newState);
//     POSTCONDITION: Cell's state is set to the new state
//
// ACCESSORS:
//     bool getState() const;  
//     POSTCONDITION: A const method - returns ell's state.  True if alive/lit, and false if dead/dark

// =================== PRIVATE CLASS MEMBERS - Cell
//   
//     bool state;  
//
// =================== PUBLIC CLASS API - GameOfLife
// MEMBER CONSTANTS:
//   const static size_t MAX_BOARD
//   The max size of the visible gameboard.  The actual size will be passed into the game's constructor. 
//
// CONSTRUCTORS:
//     GameOfLife();
//       POSTCONDITION: Creates a maximum size matrix of dark cells
//
//     GameOfLife(size_t boardSize);
//       PRECONDITION: boardSize is not greater than MAX_BOARD  
//       POSTCONDITION: Creates a boardSize-size matrix of dark cells. Sets boardSize private member.
//
//     GameOfLife(GameOfLife &game);
//       PRECONDITION: The source object for this copy-constructor exists  
//       POSTCONDITION: Creates a full copy of the referenced object
//
// MODIFIERS/MUTATORS:
//   
//  int seedBoard(string fileName);
//     FUNCIONALITY: PA1: Initializes the board; reads the configuration of lit from a text file. Returns 0/1 for sucsess/failure
//     POSTCONDITION: Board is successfully seeded with a known predictable pattern, method returns 0 (zero) to indicate success.  
//                    If the operation failed (could not open the file, wrong file format, etc), the function returns 1.
//
//   void seedBoard(string fileName) throw (FileIOexception);
//     FUNCIONALITY: PA2: Initializes the board; reads the configuration of lit cells from a text file. 
//                        May throw FileIOException 
//     POSTCONDITION: Board is successfully seeded with a known predictable pattern, method returns 0 (zero) to indicate success.  
//                    If the operation failed (could not open the file, wrong file format, etc), the function returns 1.
//
//   void seedBoard(size_t seeds);
//     FUNCTIONALITY:  Initializes the board with seeds-number of lit cells at randomly generated locations. 
//     PRECONDITION: Number of seeds requested is not greater than maximum matrix capacity  
//     POSTCONDITION: Board is successfully seeded
//                   
//   void run( );
//     FUNCTIONALITY: Starts the simulation.  Asks a user if to generate another iteration, or if to end
//     POSTCONDITION: Simulation has run until a user requested it to stop

//   void run(unsigned int numberOfIterations);
//     FUNCTIONALITY: Starts the simulation.  
//     POSTCONDITION: Simulation has run erquested number of times
//
// =================== PRIVATE CLASS MEMBERS - GameOfLife
//   
//   bool executeRule110(unsigned int countAlive, bool currentState);
//      FUNCTIONALITY: PA2:  Executes Conway set of rules (same rules as PA1)
//                     Needed for TASK #5 to develop a test harness
//                     The files test harness will be provided separately.
//      POSTCONDITION: Returns false for dead, and true for alive
//
//   bool executeRuleXXX(unsigned int countAlive, bool currentState);
//      FUNCTIONALITY: PA2 : Executes a new set of rules//                     
//      POSTCONDITION: Returns false for dead, and true for alive
//   
//   void calculateNextGen();
//     FUNCTIONALITY:  Calculates the next state of the population of Cells
//     POSTCONDITION: Next state has been calculated and is ready to display
//
// ===================  NON-MEMBER FUNCTIONS  
//
//   friend ostream& operator << (ostream& out, const GameOfLife& board)
//     POSTCONDITION: The game board has been displayed (printed to ostream out, which,
//     in turn, has been returned to the calling function)
//
//   friend istream& operator >> (istream& in, const GameOfLife& board);
//     POSTCONDITION: The game board has been populated from the input stream (file or keyboard)
//


#pragma once
#include <iostream>  // Provides ostream
#include <string>    // String operations
#include <cstdlib>   // Randomizer
#include <iomanip>

namespace csci2312
{
	using std::string;
	using std::ostream;
	using std::istream;
	using std::cin;
	// PA2: standard exception if memory allcation failed
	using std::bad_alloc;

	// Class Cell stays the same for PA1 and PA2	
	class Cell
	{
		
	public:
		static const char alive ='o';  // alive image
		static const char dead = '-';  // dead image
		
        
		Cell();
		Cell(bool cellState);  
		~Cell();

		// Accessors have no intention to modify the object, so it is a good practice to make them 'const' functions
		bool getState() const;		
		char getFace() const;

		// Mutator, also sets face, since face is based off of state
		void setState(bool newState);
			
	private:
		bool state;
		char face;		
        	
	};

	// PA2: File IO Error custom exception  class
	class FileIOException
	{
		//  Nothing inside, just a class type to handle exception
	};

	// PA2: Class GameOfLife will have some new and some changed features
    class GameOfLife
    {
		
    public:
		
		// PA2: default display board size
		static const unsigned int MAX_BOARD = 30;

		// PA2: New type (pointer to Cell type) handy with dynamic arrays
		typedef Cell* CellPtr;

		 
		// PA2: Constructs the board of the requested size, can throw exception.
		// If parameter is omitted, it becomes the default constructor, and the board will have MAX_BOARD size
		GameOfLife() throw (bad_alloc);

		// PA2:  Copy-constructor creates a new instance as a deep copy of the referenced object
		GameOfLife(const GameOfLife& game);

		// PA2:  destructor must release memory taken by dynamic arrays
		~GameOfLife();
	 

		// PA2: seeds the board from a file and throws an exception if there was trouble with file
		void seedBoard(string fileName) throw (FileIOException);

		// PA1 and PA2: seeds the  board with a given number of seeds at randomized locations
		void seedBoard(size_t seeds);
		
		//PA2: I added a rule parameter to allow user to choose which rule to use, since there are multiple rules and menu is in main
		void run(int);

		// Just an example of an possible accessor which reaches to a private array.  Not needed to satisfy PAs
		// A const(!) accessor method that returns a handle to the private currentLife array. 
		// The return type must also be 'const' because we return a pointer to a static array, and these are fixed
		// It is just an example.  It is not needed if we have a friend operator.		
		// PA2: const CellPtr* getCurrentLife() const { return currentLife; };

		// PA1 and PA2:  overloaded output operator to displsy the board 
		// friend operator can access private members of GameOfLife
		friend ostream& operator << (ostream& out, const GameOfLife& board);

		// PA2:  overloaded input operator to input the board (from file of keyboard)
		friend istream& operator >> (istream& in, const GameOfLife& board);
		
    private:	
		// PA2:  Executes Conway set of rules (same rules as PA1). Returns next state
		// Needed for TASK #5 to develop a test harness (the files test harness will be provided separately)
		bool executeRule110(unsigned int countAlive, bool currentState);

		// PA2:  Executes rule B2/S
		bool executeRuleB2_S(unsigned int countAlive, bool currentState); //rules cause all living cells to die, while maintaining same
																			//birth rules

		// PA2:  Encapsulate next generation calculation in a methos.  Needed only for OPTIONAL Task #6
		void calculateNextGen(CellPtr* current, CellPtr* next);

		// PA2:  dynamic arrays of Cells. New type CellPtr defined (typedef Cell* CellPtr)
		// currentLife and and nextLife are handles to the dynamic arrays
		CellPtr *currentLife;  
		CellPtr *nextLife;
			
		// Just an example how to declare variable cl as a handle to our array of Cells.  Not needed to satisfy PAs
		// The accessor method getCurrentLife() above uses the same syntax for the return type
		// PA2 with dynamic arrays: const CellPtr* cl = currentLife; 
	
	    // PA1 and PA2, keeps track of the actual board size, set in the constructor
	    size_t boardSize;           

		// PA2: A handle to the array that needs to be displyed next.  Only needed for OPTIONAL TASK #6 
		CellPtr displayBoard;

    };
          
   
        
}

#ifndef LIFE_CPP_PETEREDW
#define LIFE_CPP_PETEREDW

#include <iostream>
#include <vector>
#include <unistd.h> //for usleep()

#include "life.h"
#include "configs.h"

namespace {

   int get_int ();

   int get_int ()
   {
      int userInt;

      std::cin >> userInt;

      return userInt;
   }

}

namespace peteredw {

/**************************************************************
* Function: Game constructor 
* Descrption:  Creates Game with default row/column size.
* Parameters:  None 
* Pre-conditions: None
* Post-conditions: None
**************************************************************/

   Game::Game() {

      configList.resize(2);

      configList = {pulsar, gosper};

   }

   void Game::play() {

      std::cout << "Welcome to Conway's life!\n";

      config_menu();

      std::cout << "Enter the number of generations you would like to see: ";
      user_gens();
      std::cout << std::endl;

      run_game();

   }

   void Game::add_config(Config newConfig) {

      configList.push_back(newConfig);
   
   }

   void Game::config_menu() {

      for (unsigned int i = 0; i < configList.size(); i++) {

         std::cout << (i + 1) << ". " << (configList.at(i)).title()
                     << std::endl;
      
      }

      std::cout << "Enter the number corresponding to the configuration you "
               << "want to play: ";

      confChoice = get_int();

      while (confChoice < 1 || (unsigned int)confChoice > configList.size())
      {

         std::cout << "Invalid entry. Please enter a number between "
                     << "1 and " << configList.size() << ": ";

         confChoice = get_int();
         
         std::cout << std::endl;
      
      }

   }

   void Game::user_gens() {

      numGens = get_int();
   
   }

   void Game::run_game() {

      std::cout << "Entered run_game\n";

      std::cout << "confChoice = " << confChoice << std::endl;
      
      Board gameBoard = Board(configList.at(confChoice - 1));

      gameBoard.print();

      for (int i = 0; i < numGens; i++)
      {

         try {

            gameBoard.next();
            gameBoard.print();
         
         }

         catch (BoardStatic) {
            
            std::cout << "The game board has stopped changing, "
                        << "so the game is over.\n";

            return;

         }
      }

      std::cout << numGens << " generations have been printed, "
                  << "so the game is over.\n";

      return;
   
   }

   Config::Config() {};

/**************************************************************
* Function: Config constructor 
* Descrption:  Creates a configuration (for initializing a board)
*              with specified values. 
* Parameters:  newConfig - 2d vector of bools
*                          (bools become Cells)
*              title -     Name of the configuration.              
* Pre-conditions: None
* Post-conditions: None
**************************************************************/

   Config::Config(const std::vector<std::vector<bool>> &newConfig,
                  std::string title) 
                  : name(title) {

      configuration.resize(newConfig.size());

      for (unsigned int i = 0; i < newConfig.size(); i++) {
         
         configuration[i].resize(newConfig[i].size());

         for (unsigned int j = 0; j < newConfig[0].size(); j++)
            configuration[i][j] = Cell(newConfig[i][j]);
      
      }
   }

   std::string Config::title() {

      return name;
   
   }


   std::vector<std::vector<Cell>> Config::cells() const {

         return configuration;
   }

   Board::Board(Config initConfig) {

      lastGen.resize((initConfig.cells()).size());
  
      for (unsigned int i = 0; i < lastGen.size(); i++)
         lastGen[i].resize((initConfig.cells())[i].size());

      nextGen = initConfig.cells();
   
   }

   void Board::next() throw(BoardStatic) {

      bool newCellState, noChange = 1;

      //Make lastGen a copy of nextGen.
      lastGen = nextGen;

      //Fill nextGen with next generation's cell states
      //based on lastGen's cell states.
      for (unsigned int i = 0; i < nextGen.size(); i++) {

         for (unsigned int j = 0; j < nextGen[0].size(); j++) {
            
            newCellState = (lastGen[i][j]).next(lastGen, i, j);
            
            //If not a single cell has changed since the last generation,
            //noChange will be true after the for loops.
            if (newCellState != lastGen[i][j].status())
               noChange = false;

            nextGen[i][j] = Cell(newCellState);
         
         }
      }

      if (noChange)
         throw BoardStatic();

      return;
   
   }

//Prints nextGen.
   void Board::print() {

   for (unsigned int i = 0; i < nextGen.size(); i++) {
      if (i == (nextGen.size() - 1))
         usleep(250000);
      std::cout << "\n";
      for (unsigned int j = 0; j < nextGen[0].size(); j++)
        
         if (nextGen[i][j].status() == 1)
            std::cout << "\033[41m \033[0m";
         else
            std::cout << " ";
   }

      return;
   }

   Cell::Cell() {}

/**************************************************************
* Function: Cell constructor 
* Descrption:  Creates Cell with status of alive (true) or 
*              dead.
* Parameters: bool value (alive = true, dead = false)
* Pre-conditions: None
* Post-conditions: None
**************************************************************/

   Cell::Cell(bool value) {

      state = value;
   
   }

/**************************************************************
* Function: Cell::status() 
* Descrption:  Returns value of state.
* Parameters: None
* Pre-conditions: None 
* Post-conditions: None
**************************************************************/

   bool Cell::status() const {

      return state;
   
   }

   bool Cell::next(std::vector<std::vector<Cell>> &container,
                           int rowPos, int colPos)
                           throw(BadNeighborNum)
   {
         
      int numNeighbors = count_neighbors(container, rowPos, colPos);
      
      if (numNeighbors < 0 || numNeighbors > 8)
         throw BadNeighborNum();

      if (state == true) {    //if currently alive
         
         if (numNeighbors < 2)      //if underpopulated
            return false;              //dead next time
         
         else if (numNeighbors < 4) //if equilibrium (2 or 3 neighbs)
            return true;               //alive next time
         
         else if (numNeighbors > 4) //if overpopulated
            return false;              //dead next time
      }

      else if (state == false) { //if currently dead

         if (numNeighbors == 3)     //if neighbs reproductive
            return true;               //alive next time     
      }
      else {
         
         std::cout << "Major error in Cell::next(). Program will exit.";
         exit(-1);

      }

      return false;
   }

//I was said to have to pass in the row/col nums for
//the Cell, but I can't think of a way the Cell could
//efficiently determine this itself.
   int Cell::count_neighbors(const std::vector<std::vector<Cell>> &container,
                              int rowPos, int colPos) const {

      //std::cout << "Entered count_neighbors().\n"; //DEBUGGING

      int numNeighbors = 0;

      //To store the absolute coordinates of whatever surrounding Cell is
      //being counted at the moment.
      //rOffset is the its row #, cOffset is its col #.
      int rOffset, cOffset; 

      //Number of rows & cols to modulate by
      int rows = container.size(), cols = container[0].size();

      //std::cout << "container # of rows: " << rows
      //             << ", cols: " << cols << std::endl; //DEBUGGING

      //Generate each offset coordinates for the 8 surrounding Cells,
      //then check each one's status (alive or dead). If it's alive,
      //add 1 to numNeighbors.
      for (int i = -1; i <= 1; i++) {
         
         //std::cout << "i (should go from -1 to 1): " << i << std::endl;
         
         for (int j = -1; j <= 1; j++) {
         
            //std::cout << "j (should go from -1 to 1): " << j << std::endl;
            
            if (i != 0 || j != 0) {

               //Adding rows & cols to the modulated numbers ensures rOffset
               //and cOffset are positive.
               rOffset = (rowPos + i + rows) % rows;
               cOffset = (colPos + j + cols) % cols;

               numNeighbors +=
                  container[rOffset][cOffset].status();

               //std::cout << "numNeighbors = " << numNeighbors << std::endl;
            }
         }
      }
      
      return numNeighbors; 
   }
}


#endif

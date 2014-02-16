#ifndef LIFE_H_PETEREDW
#define LIFE_H_PETEREDW

#include <string>
#include <vector>

namespace peteredw {

   class BadNeighborNum {};

   class BoardStatic {};

   class NoSuchConfig{};

   class Cell {

      public:

         friend class Board;
         
         Cell();

         Cell(bool value);

         bool status() const;

      private:

         bool next(std::vector<std::vector<Cell>> &container,
               int rowPos, int colPos) throw(BadNeighborNum); 

         int count_neighbors(
               const std::vector<std::vector<Cell>> &container,
               int rowPos, int colPos) const; 

         bool state;

   };

   class Config {

      public:

         Config();

         Config(const std::vector<std::vector<bool>> &newConfig,
                  std::string title);

         std::string title();

         std::vector<std::vector<Cell>> cells() const;

      private:

         std::string name;

         std::vector<std::vector<Cell>> configuration;

   };

   class Board {

      public:

         Board(Config initConfig);

         void next() throw (BoardStatic);

         void print();

      private:

         std::vector<std::vector<Cell>> nextGen;

         std::vector<std::vector<Cell>> lastGen;
   
   };

   class Game {

      public:

         Game();

         void play();

         void add_config(Config newConfig);

      private:

         std::vector<Config> configList;

         int confChoice, numGens;

         void config_menu();

         void user_gens();

         void run_game();
   
   };

}

#endif

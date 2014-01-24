#ifndef LIFE_H_PETEREDW
#define LIFE_H_PETEREDW

namespace peteredw {

   class Game {

      public:

         Game();

         void play();

         void add_config(Config newConfig, int height, int width);

      private:

         ConfigSet configList;

         int confChoice, numGens, rows, cols;

         void config_menu();

         void user_gens();

         void run_game;

         void dims(int height, int width);
   
   };

   class ConfigSet {

      public:

         ConfigSet();

         int num();

         std::string name(int index);

         Config conf(int index) throw (NoSuchConfig);

         void add(Config newConfig);

         void empty();

      private:

         int setSize;

         Config set[];
   };

   class Config {

      public:

         Config(bool ** arr, std::string name int height, int width);

         std::string get_names();

         Cell ** get_cells();

      private:

         std::string name;

         Cell ** configuration[];

         int rows, cols;
   };

   class Board {

      public:

         Board(Config initial, int height, int width);

         friend class Cell;

         void next() throw (BoardStatic);

         void print();

      private:

         Cell ** nextGen;

         Cell ** lastGen;

         int rows, cols;
   };

   class Cell {

      public:

         Cell(bool value);

         bool status();

         bool next_state();

      private:

         bool state;

         int count_neighbors();
   };

   class BoardStatic {};

   class NoSuchConfig{};
}

#endif

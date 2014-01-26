#ifndef LIFE_CPP_PETEREDW
#define LIFE_CPP_PETEREDW

#include "life.h"
#include <cstdlib> //for exit()
#include <climits> //for INT_MAX

namespace {

   int get_int (int lowBound, int highBound = 0);

   int get_int (int lowBound, int highBound)
   {
      return 0;
   }

   peteredw::Config * defaultConfigs;

   int NUM_DEFAULTS;
}

namespace peteredw {

   Game::Game() {

      rows = 22;
      cols = 88;

   }

   void Game::play() {

      return;   

   }

   void Game::add_config(Config newConfig, int height, int width) {

      return;
   
   }

   void Game::config_menu() {

      return;
   
   }

   void Game::user_gens() {

      return;
   
   }

   void Game::run_game() {

      return;
   
   }

   void Game::dims (int height, int width) {

      return;
   
   }

   ConfigSet::ConfigSet() {
   
   }
   
   int ConfigSet::num() {

      return 0;
   
   }

   std::string ConfigSet::name(int index) {

      std::string tempReturn = "name";

      return tempReturn;
   
   }

   Config::Config(bool ** arr, std::string name, int height, int width) {
   
   }

   std::string Config::title() {

      std::string tempReturn = "name";

      return tempReturn;
   
   }

   Cell ** Config::cells() {

      Cell ** temp;

      return temp;
   
   }

   Board::Board(Config initConfig, int height, int width) {
   
   }

   void Board::next() throw(BoardStatic) {

      return;
   
   }

   void Board::print() {

      return;
   
   }

   Cell::Cell(bool value) {
   
   }

   bool Cell::status() {

      return 0;
   
   }

   bool Cell::next_state() {

      return 0;
   
   }

   int Cell::count_neighbors() {

      return 0;
   
   }
}


#endif

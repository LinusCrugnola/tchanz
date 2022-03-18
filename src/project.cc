/****************************************************************!
  \file     project.cc
  \author   Léo Brückl, Linus Crugnola
  \date     18.03.2022
  \brief    main file of tchanz project
*****************************************************************/

#include <iostream>
#include <string>
//#include "squarecell.h"
using namespace std;

string get_testfile(int argc, char *argv[]){
  string filename;
  if(argc>0){
    filename = argv[1];
  }
}

int main(int argc, char *argv[]){
  // Squarecell grid(5);
  // grid.print_grid();
  // //grid.set_coordinate(1,4);
  // grid.square_add(2,2,3,1);
  // grid.print_grid();
  // grid.square_validation_test(2,6,3,1);
  cout << get_testfile(argc, argv) << endl;
}

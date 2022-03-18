/****************************************************************!
  \file     project.cc
  \author   Léo Brückl, Linus Crugnola
  \date     date
  \brief    main file of tchanz project
*****************************************************************/

#include <iostream>
#include "squarecell.h"
using namespace std;

int main(){
  Squarecell grid(5);
  grid.print_grid();
  //grid.set_coordinate(1,4);
  grid.square_add(2,2,3,1);
  grid.print_grid();
  grid.square_validation_test(2,6,3,1);
}
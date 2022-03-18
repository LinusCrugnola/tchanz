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
  uint max = grid.get_gmax();
  cout<<max<<endl;
}
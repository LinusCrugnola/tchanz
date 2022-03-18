/****************************************************************!
  \file     test_squarecell.cc
  \author   Léo Brückl, Linus Crugnola
  \date     18.03.2022
  \brief    squarecell test
*****************************************************************/

#include "../src/squarecell.h"
#include <iostream>


int main(){
  Squarecell grid(16);
  grid.square_validation_test(20,20,3,0);
}

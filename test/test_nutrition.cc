/******************************************************************************!
* @file     test_nutrition.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

#include "../nutrition.h"
#include "../squarecell.h"
#include "testfunctions.h"

using namespace std;

void test_nutrition(){
    // Test constructor:
    cout << "Test nutrition" << endl;
    Nutrition nutri;

    // Test data validation
    string line = " 20 55";
    istringstream data(line);
    nutri.add_element(data);
    assert(square_superposition({20,55,1,0}));
    cout << "Test 1 passed" << endl;

}
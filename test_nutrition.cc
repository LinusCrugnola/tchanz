/******************************************************************************!
* @file     test_nutrition.cc
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

#include "nutrition.h"
#include "squarecell.h"

using namespace std;

int main(){
    // Test constructor:
    cout << "Test nutrition" << endl;
    Nutrition nutri(1,1);
    assert(square_superposition({1,1,1,1}));
    cout << "Test 1 passed" << endl;

    // Test data validation
    string line = " 20 55";
    istringstream data(line);
    Nutrition::data_validation(data);
    assert(square_superposition({20,55,1,0}));
    cout << "Test 2 passed" << endl;

}
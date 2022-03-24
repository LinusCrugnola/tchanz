/****************************************************************!
 \file     test_nutrition.cc
 \author   Léo Brückl, Linus Crugnola
 \date     24.03.2022
 \brief    test_nutrition implementation
*****************************************************************/
#include <cassert>
#include <iostream>

#include "../src/nutrition.h"
#include "../src/squarecell.h"

using namespace std;

int main(){
    // Test constructor:
    cout << "Test nutrition" << endl;
    Nutrition nutri(1,1);
    assert(square_superposition({1,1,1,1}));
    cout << "Test 1 passed" << endl;
}
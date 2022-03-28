/****************************************************************!
  \file     test_squarecell.cc
  \author   Léo Brückl, Linus Crugnola
  \date     22.03.2022
  \brief    squarecell test
*****************************************************************/

#include "../src/squarecell.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(){
    //square error = {500,500,0,0};

    // Test of validation function
    assert(square_validation({0,0,1,1}));
    cout << "Test 1 passed" << endl;
    assert(square_validation({g_max-1,g_max-1,1,1}));
    cout << "Test 2 passed" << endl;
    assert(square_validation({0,0,g_max,0}));
    cout << "Test 3 passed" << endl;
    assert(square_validation({0,0,g_max,0}));

    // Test of square add function
    assert(square_add({0,0,4,0}));
    cout << "Test 4 Passed" << endl;
    assert(square_add({g_max-2,g_max-2,3,1}));
    cout << "Test 5 Passed" << endl;
    
    // Test of superposition function
    // assert((square_superposition({g_max-2,g_max-2,3,1})==error));
    // cout << "Test 6 Passed" << endl;
    // assert((square_superposition({0,0,4,0})==error));
    // cout << "Test 7 Passed" << endl;
    // assert(square_superposition({6,6,3,1}));
    // cout << "Test 8 Passed" << endl;

    assert(square_superposition({2,2,3,1}, {4,4,3,1}));
    cout << "Test 9 Passed" << endl;
    assert(square_superposition({2,2,3,1}, {3,3,3,1}));
    cout << "Test 10 Passed" << endl;
    assert(square_superposition({2,2,3,1}, {2,2,3,1}));
    cout << "Test 11 Passed" << endl;
    assert(square_superposition({2,2,3,1}, {5,2,3,1})==false);
    cout << "Test 12 Passed" << endl;
    assert(square_superposition({2,2,3,1}, {2,2,1,1}));
    cout << "Test 13 Passed" << endl;

    // Test of contains function
    assert(square_contains({1,1,5,0}, {3,3,3,1}));
    cout << "Test 14 Passed" << endl;
    assert(square_contains({0,0,3,0}, {1,1,1,1}));
    cout << "Test 15 Passed" << endl;
    assert(square_contains({1,1,5,0}, {6,6,1,1})==false);
    cout << "Test 16 Passed" << endl;
    assert(square_contains({2,2,3,0}, {2,2,1,1})==false);
    cout << "Test 17 Passed" << endl;

    // // Test of square delete function
    // assert(square_delete({0,0,4,0}));
    // assert(square_superposition({0,0,4,0})==false);
    // cout << "Test 18 Passed" << endl;
    // assert(square_delete({g_max-2,g_max-2,3,1}));
    // cout << "Test 19 Passed" << endl;
    // assert(square_superposition({g_max-2,g_max-2,3,1})==false);
    // cout << "Test 20 Passed" << endl;
    // assert(square_delete({g_max-2,g_max-2,3,1})==false);
    // cout << "Test 21 Passed" << endl;

}

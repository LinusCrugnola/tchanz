/******************************************************************************!
* @file     test_squarecell.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include "../squarecell.h"
#include "testfunctions.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_squarecell(){
    
    // Test of validation function
    assert(scl::square_validation({0,0,1,1}));
    cout << "Test 1 passed" << endl;
    assert(scl::square_validation({scl::g_max-1,scl::g_max-1,1,1}));
    cout << "Test 2 passed" << endl;
    assert(scl::square_validation({0,0,scl::g_max,0}));
    cout << "Test 3 passed" << endl;
    assert(scl::square_validation({0,0,scl::g_max,0}));

    // Test of square add function
    assert(scl::square_add({0,0,4,0}));
    cout << "Test 4 Passed" << endl;
    assert(scl::square_add({scl::g_max-2,scl::g_max-2,3,1}));
    cout << "Test 5 Passed" << endl;
    
    // Test of square superposition function
    assert(scl::square_superposition({scl::g_max-2,scl::g_max-2,3,1}));
    cout << "Test 6 Passed" << endl;
    assert(scl::square_superposition({0,0,4,0}));
    cout << "Test 7 Passed" << endl;
    assert(scl::square_superposition({6,6,3,1})==false);
    cout << "Test 8 Passed" << endl;

    assert(scl::square_superposition({2,2,3,1}, {4,4,3,1}));
    cout << "Test 9 Passed" << endl;
    assert(scl::square_superposition({2,2,3,1}, {3,3,3,1}));
    cout << "Test 10 Passed" << endl;
    assert(scl::square_superposition({2,2,3,1}, {2,2,3,1}));
    cout << "Test 11 Passed" << endl;
    assert(scl::square_superposition({2,2,3,1}, {5,2,3,1})==false);
    cout << "Test 12 Passed" << endl;
    assert(scl::square_superposition({2,2,3,1}, {2,2,1,1}));
    cout << "Test 13 Passed" << endl;

    // Test of get superposition function
    scl::square test_square;
    test_square=scl::square_get_superposition({scl::g_max-2,scl::g_max-2,3,1});
    if(test_square.x == scl::g_max-3 && test_square.y == scl::g_max-1 && test_square.side == 1 && test_square.centered == 1){
        cout << "Test 14 Passed" << endl;
    }
    else exit(EXIT_FAILURE);
    test_square=scl::square_get_superposition({0,0,4,0});
    if(test_square.x == 0 && test_square.y == 3 && test_square.side == 1 && test_square.centered == 1){
        cout << "Test 15 Passed" << endl;
    }
    else exit(EXIT_FAILURE);
    test_square=scl::square_get_superposition({6,6,3,1});
    if(test_square.x == 500 && test_square.y == 500 && test_square.side == 0 && test_square.centered == 0){
        cout << "Test 16 Passed" << endl;
    }
    else exit(EXIT_FAILURE);

    // Test of contains function
    assert(scl::square_contains({1,1,5,0}, {3,3,3,1}));
    cout << "Test 17 Passed" << endl;
    assert(scl::square_contains({0,0,3,0}, {1,1,1,1}));
    cout << "Test 18 Passed" << endl;
    assert(scl::square_contains({1,1,5,0}, {6,6,1,1})==false);
    cout << "Test 19 Passed" << endl;
    assert(scl::square_contains({2,2,3,0}, {2,2,1,1})==false);
    cout << "Test 20 Passed" << endl;

    // Test of square delete function
    assert(scl::square_delete({0,0,4,0}));
    assert(scl::square_superposition({0,0,4,0})==false);
    cout << "Test 21 Passed" << endl;
    assert(scl::square_delete({scl::g_max-2,scl::g_max-2,3,1}));
    cout << "Test 22 Passed" << endl;
    assert(scl::square_superposition({scl::g_max-2,scl::g_max-2,3,1})==false);
    cout << "Test 23 Passed" << endl;
    assert(scl::square_delete({scl::g_max-2,scl::g_max-2,3,1})==false);
    cout << "Test 24 Passed" << endl;

    // // Test of touch function
    // //one
    // cout << scl::square_touch({3,3,3,1},{1,1,1,1}) << endl;
    // cout << scl::square_touch({3,3,3,1},{5,1,1,1}) << endl;
    // cout << scl::square_touch({3,3,3,1},{5,5,1,1}) << endl;
    // cout << scl::square_touch({3,3,3,1},{1,5,1,1}) << endl;
    // cout << scl::square_touch({3,3,3,1},{1,3,1,1}) << endl;
    // cout << scl::square_touch({3,3,3,1},{3,1,1,1}) << endl;
    // cout << scl::square_touch({3,3,3,1},{5,3,1,1}) << endl;
    // cout << scl::square_touch({3,3,3,1},{3,5,1,1}) << endl;
    // //right  
    // cout << "---" << endl;
    // cout << scl::square_touch({4,4,3,1},{7,0,3,1}) << endl;
    // cout << scl::square_touch({4,4,3,1},{7,1,3,1}) << endl;
    // cout << scl::square_touch({4,4,3,1},{7,3,3,1}) << endl;
    // cout << scl::square_touch({4,4,3,1},{7,6,3,1}) << endl;
    // cout << scl::square_touch({4,4,3,1},{7,7,3,1}) << endl;
    // cout << scl::square_touch({4,4,3,1},{7,8,3,1}) << endl;
    // //left
    // cout << "---" << endl;
    // cout << scl::square_touch({6,4,3,1},{3,0,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{3,1,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{3,3,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{3,6,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{3,7,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{3,8,3,1}) << endl;
    // // up
    // cout << "---" << endl;
    // cout << scl::square_touch({6,4,3,1},{2,7,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{3,7,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{6,7,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{8,7,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{9,7,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{10,7,3,1}) << endl;
    // // down
    // cout << "---" << endl;
    // cout << scl::square_touch({6,4,3,1},{2,1,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{3,1,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{6,1,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{8,1,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{9,1,3,1}) << endl;
    // cout << scl::square_touch({6,4,3,1},{10,1,3,1}) << endl;
    // //Test get_3x3:
    // cout << "---" << endl;
    // //empty grid
    // scl::square s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({100,100,9,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;

    // s = scl::get_free3x3({10,10,5,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;
    // scl::square_add(s);

    // s = scl::get_free3x3({10,10,5,0});
    // cout << s.x << " " << s.y << " " << s.side << " " << s.centered << endl;


    scl::square_add({34,6,5,1});
    scl::square_add({34,10,3,1});
    scl::square_add({42,5,3,1});
    scl::square_add({46,5,3,1});
    scl::square s = scl::get_free3x3({30,1,16,0});

    cout << s << endl;

    scl::vector v = {1,1};
    s = s + v;

    v.rotate();
    cout << v << endl;
    v.rotate();
    cout << v << endl;
    v.rotate();
    cout << v << endl;
    v.rotate();
    cout << v << endl;

    cout << s << endl;

    scl::square lol = {0,0,1,1};
    cout << lol+v << endl;
    cout << lol+v << endl;

    scl::square s1 = {1,1,2,1};
    scl::square s2 = {5,5,4,1};

    cout <<  (s1 == s1) << endl;
    cout << (s2 == s2) << endl;
    cout << (s1 == s2) << endl;
    cout << (s1 != s2) << endl;
    cout << (s1 != s1) << endl;
}

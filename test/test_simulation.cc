/******************************************************************************!
* @file     test_simulation.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/
 
#include <cassert>
#include <iostream>

#include "../simulation.h"
#include "testfunctions.h"

void test_simulation(){
    Simulation simu;
    std::cout << "\n------------------------- First file ------------------------------" << std::endl;
    simu.read_configfile("testfiles/t01.txt");
    simu.clear();
    std::cout << "\n------------------------- Second file ------------------------------" << std::endl;
    simu.read_configfile("testfiles/t01.txt");
    simu.clear();
    std::cout << "\n------------------------- Third file ------------------------------" << std::endl;
    simu.read_configfile("testfiles/t01.txt");
    simu.clear();
}
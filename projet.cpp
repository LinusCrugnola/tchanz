/******************************************************************************!
* @file     projet.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     100%
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include <iostream>
#include <string>

#include "squarecell.h"
#include "simulation.h"
#include "message.h"

/**
 * @brief Main module of Tchanz project (highest priority)
 */

std::string state_read =  "--------------------- File Lecture ----------------------";
std::string state_clear = "--------------------- Abort Lecture ---------------------";
std::string state_write = "--------------------- Generate File ---------------------";


/**
 * @brief project main function
 */
int main(int argc, char **argv){

    //create a simulation and set up the map
    Simulation simulation;

    std::cout << state_read << std::endl;

    // get the name of the configfile
    std::string filename = argc > 1 ? argv[1] : "";
    
    if(!simulation.read_configfile(filename)){
        std::cout << state_clear << std::endl;
        simulation.clear();
    }
    else{
        std::cout << message::success();
        std::cout << state_write << std::endl;
        simulation.write_configfile();
    }
    //destroy the simulation and all of its allocated data
    simulation.~Simulation();
    exit(EXIT_SUCCESS);
}
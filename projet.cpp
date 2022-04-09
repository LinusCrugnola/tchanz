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

using namespace std;

/**
 * @brief Main module of Tchanz project (highest priority)
 */

std::string read = "---------- File Lecture ----------";
std::string clear = "---------- Abort Lecture ----------";
std::string write = "---------- Generate File ----------";

/**
 * @brief Get the name of the testfile
 * 
 * @param argc 
 * @param argv 
 * @return string 
 */
string get_testfile(int argc, char **argv);

/**
 * @brief project main function
 */
int main(int argc, char **argv){
    //create a simulation and set up the map
    Simulation simulation;

    std::cout << read << std::endl;

    if(!simulation.read_configfile(get_testfile(argc, argv))){
        std::cout << clear << std::endl;
        simulation.clear();
    }

    //cout << message::success();

    else{
        std::cout << write << std::endl;
        simulation.write_configfile();
    }
    //destroy the simulation and all of its allocated data
    //simulation.~Simulation();
    exit(EXIT_SUCCESS);
}

string get_testfile(int argc, char **argv){
	string filename;
	if(argc>1){
		filename = argv[1];
	}
	else{
		cout << "False file" << endl;
		exit(0);
	}
	return filename;
}
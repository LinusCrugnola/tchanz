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
    Simulation simulation;
    simulation.read_configfile(get_testfile(argc, argv));
    cout << message::success() ;
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
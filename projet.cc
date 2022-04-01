/******************************************************************************!
* @file     projet.cc
* @author   Léo Brückl <leo.bruckl@epfll.ch>            
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

// Function to get name of textfile (ending must be .txt)
string get_testfile(int argc, char **argv);

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
/****************************************************************!
	\file     project.cc
	\author   Léo Brückl, Linus Crugnola
	\date     31.03.2022
	\brief    main file of tchanz project
*****************************************************************/

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
	// size_t check = filename.rfind(".txt");
	// if(filename.length()-check != 4){
	// 	cout << "no txt file" << endl;
	// 	exit(0);
	// }
	return filename;
}
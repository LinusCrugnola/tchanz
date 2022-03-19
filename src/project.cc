/****************************************************************!
	\file     project.cc
	\author   Léo Brückl, Linus Crugnola
	\date     18.03.2022
	\brief    main file of tchanz project
*****************************************************************/

#include <iostream>
#include <string>
#include "squarecell.h"
#include "simulation.h"
using namespace std;

// TODO: replace exit();
// Function to get name of textfile (ending must be .txt)
string get_testfile(int argc, char **argv){
	string filename = "myfile";
	if(argc>1){
		filename = argv[1];
	}
	else{
		cout << "False file" << endl;
		exit(0);
	}
	size_t check = filename.rfind(".txt");
	if(filename.length()-check != 4){
		cout << "no txt file" << endl;
		exit(0);
	}
	return filename;
}

int main(int argc, char **argv){

}

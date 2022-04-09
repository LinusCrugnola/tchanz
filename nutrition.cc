/******************************************************************************!
 * @file     nutrition.cc
 * @author   Léo Brückl <leo.bruckl@epfl.ch>             70 %
 *           Linus Crugnola <linus.crugnola@epfl.ch>     30 %
 * @version  1.0
 * @date     01.04.2022
 *******************************************************************************/

#include "nutrition.h"

#include <iostream>

#include "error_squarecell.h"
#include "message.h"

using namespace std;

void Nutrition::add_element(istringstream& data) {
    bool valid = true;
    square position = {0,0,1,1};
    if (!(data >> position.x >> position.y)) cout << "reading error!" << endl;

    valid = square_validation(position); // displays error if invalid

    if (square_superposition(position)) {
        cout << message::food_overlap(position.x, position.y);
        valid = false;
    }

    if(valid){
        //add element to map
        //block square

        //temp
        square_add(position);
        this->foods.push_back(position);
    }
}

string Nutrition::get_filedata(){
    string output = {};
    output += "# \n";
    output += "# nb food\n" + to_string(this->foods.size()) + "\n\n# food \n";
    for(auto elem : this->foods){
        output += to_string(elem.x) + "  " + to_string(elem.y) + "\n";
    }
    return output;
}
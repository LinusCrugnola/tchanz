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

bool Nutrition::add_element(std::istringstream& data) {
    bool valid = true;
    square position = {0,0,1,1};
    if (!(data >> position.x >> position.y)) 
        return false;

    valid = square_validation(position); // displays error if invalid

    if (square_superposition(position)) {
        std::cout << message::food_overlap(position.x, position.y);
        valid = false;
    }

    if(valid){
        //add element to map
        //block square

        //temp
        square_add(position);
        this->foods.push_back(position);
        return true;
    }
    return false;
}

std::string Nutrition::get_filedata(){
    std::string output = {};
    output += "# \n\n";
    output += "# nb food\n" + std::to_string(this->foods.size()) + "\n\n# food \n";
    for(auto elem : this->foods){
        output += std::to_string(elem.x) + "  " + std::to_string(elem.y) + "\n";
    }
    return output;
}

void Nutrition::clear(){
    for(auto elem : foods){
        square_delete(elem);
    }
    this->foods.clear();
}

Nutrition::~Nutrition(){
    for(auto elem : this->foods){
        square_delete(elem);
    }
    this->foods.clear();
}
/******************************************************************************!
* @file     defensor.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#include "defensor.h"

#include <iostream>

#include "message.h"

Defensor::Defensor(scl::csquare position, unsigned age)
    : Ant(position), age(age) {
    scl::square_add(position);
}

bool Defensor::draw(graphic::color color){
    return scl::square_draw(this->position, scl::cross, color);
}

Ant* Defensor::data_validation(std::istringstream& data,
                               scl::csquare anthill_position,
                               const unsigned& home) {
    Ant* defensor = nullptr;
    scl::square position = {0, 0, sizeD, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age))
        std::cout << "reading error!" << std::endl;

    if(!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        scl::square overlap = scl::square_get_superposition(position);
        std::cout << message::defensor_overlap(position.x, position.y,
                                               overlap.x, overlap.y);
        return nullptr;
    }

    if (!scl::square_contains(anthill_position, position)) {
        std::cout << message::defensor_not_within_home(position.x, position.y, home);
        return nullptr;
    }

    defensor = new Defensor(position, age);
    return defensor;
}

std::string Defensor::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
                + std::to_string(this->position.y) + " " 
                + std::to_string(this->age) + "\n";
}
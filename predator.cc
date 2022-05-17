/******************************************************************************!
* @file     predator.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#include "predator.h"

#include <iostream>

#include "message.h"

Predator::Predator(scl::csquare position, unsigned age, unsigned hill_index)
    : Ant(position, hill_index, true), age(age) {
    scl::square_add(position);
}
bool Predator::action(scl::csquare hill_pos){
    return true;
}

bool Predator::draw(graphic::color color) {
    return scl::square_draw(this->position, scl::uniform, color);
}

Ant* Predator::data_validation(std::istringstream& data, unsigned hill_index) {
    Ant* predator = nullptr;
    scl::square position = {0, 0, sizeP, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age))
        std::cout << "reading error!" << std::endl;

    if (!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        std::cout << message::predator_overlap(position.x, position.y);
        return nullptr;
    }

    predator = new Predator(position, age, hill_index);
    return predator;
}

std::string Predator::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
                + std::to_string(this->position.y) + " "
                + std::to_string(this->age) + "\n";
}
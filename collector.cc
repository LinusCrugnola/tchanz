/******************************************************************************!
* @file     collector.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#include "collector.h"

#include <iostream>

#include "message.h"

Collector::Collector(scl::csquare position, unsigned age, Etat_collector food_state)
    : Ant(position), age(age), food_state(food_state) {
    scl::square_add(position);
}

bool Collector::draw(graphic::color color) {
    bool error = false;
    error = scl::square_draw(this->position, scl::diagonal, color);
    if (this->food_state == LOADED) {
        error |= scl::square_draw({this->position.x, this->position.y, 1, 1}, 
                                  scl::rhomb, {1, 1, 1});
    }
    return error;
}

Ant* Collector::data_validation(std::istringstream& data) {
    Ant* collector = nullptr;
    scl::square position = {0, 0, sizeC, 1};
    unsigned age;
    std::string food;
    Etat_collector food_state;
    if (!(data >> position.x >> position.y >> age >> food))
        std::cout << "reading error!" << std::endl;
    food_state = food == "true" ? LOADED : EMPTY;

    if (!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        scl::square overlap = scl::square_get_superposition(position);
        std::cout << message::collector_overlap(position.x, position.y,
                                                overlap.x, overlap.y);
        return nullptr;
    }

    collector = new Collector(position, age, food_state);
    return collector;
}

std::string Collector::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
           + std::to_string(this->position.y) + " " + std::to_string(this->age) + " "
           + (this->food_state == LOADED ? "true" : "false") + "\n";
}
/******************************************************************************!
* @file     collector.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#include "collector.h"

#include <iostream>

#include "message.h"

Collector::Collector(scl::csquare position, unsigned age, Etat_collector food)
    : Ant(position), age(age), food(food) {
    scl::square_add(position);
}

bool Collector::draw(graphic::color color){
    return scl::square_draw(this->position, scl::diagonal, color);
}

Ant* Collector::data_validation(std::istringstream& data) {
    Ant* collector = nullptr;
    scl::square position = {0, 0, sizeC, 1};
    unsigned age;
    std::string food_state;
    Etat_collector food;
    if (!(data >> position.x >> position.y >> age >> food_state))
        std::cout << "reading error!" << std::endl;
    food = food_state == "true" ? LOADED : EMPTY;

    if(!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        scl::square overlap = scl::square_get_superposition(position);
        std::cout << message::collector_overlap(position.x, position.y,
                                                overlap.x, overlap.y);
        return nullptr;
    }

    collector = new Collector(position, age, food);
    return collector;
}

std::string Collector::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
           + std::to_string(this->position.y) + " " + std::to_string(this->age) + " "
           + (this->food == LOADED ? "true" : "false") + "\n";
}
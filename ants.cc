/******************************************************************************!
 * @file     ants.cc
 * @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
 *           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
 * @version  1.0
 * @date     01.04.2022
 *******************************************************************************/

#include "ants.h"

#include <iostream>
#include <string>

#include "constantes.h"
#include "message.h"
#include "squarecell.h"

Ant::Ant(square position)
    : position(position) {
    square_add(position);
};

Ant::~Ant(){
    square_delete(this->position);
}

Generator::Generator(csquare position)
    : Ant(position) {
    square_add(position);
}

Ant* Generator::data_validation(coord xg, coord yg,
                                csquare anthill_position,
                                const unsigned& home) {
    Ant* generator = nullptr;
    square position = {xg, yg, sizeG, 1};

    if(!square_validation(position)) return nullptr;

    if (square_superposition(position)) {
        square overlap = square_get_superposition(position);
        std::cout << message::generator_overlap(position.x, position.y, overlap.x,
                                           overlap.y);
        return nullptr;
    }

    if (!square_contains(anthill_position, position)) {
        std::cout << message::generator_not_within_home(position.x, position.y, home);
        return nullptr;
    }

    generator = new Generator(position);
    return generator;
}

std::string Generator::get_filedata(){
    return std::to_string(this->position.x) + " " + std::to_string(this->position.y);
}

Collector::Collector(csquare position, unsigned age, Etat_collector food)
    : Ant(position), age(age), food(food) {
    square_add(position);
}

Ant* Collector::data_validation(std::istringstream& data) {
    Ant* collector = nullptr;
    square position = {0, 0, sizeC, 1};
    unsigned age;
    std::string food_state;
    Etat_collector food;
    if (!(data >> position.x >> position.y >> age >> food_state))
        std::cout << "reading error!" << std::endl;
    food = food_state == "true" ? LOADED : EMPTY;

    if(!square_validation(position)) return nullptr;

    if (square_superposition(position)) {
        square overlap = square_get_superposition(position);
        std::cout << message::collector_overlap(position.x, position.y,
                                                overlap.x, overlap.y);
        return nullptr;
    }

    collector = new Collector(position, age, food);
    return collector;
}

std::string Collector::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
           + std::to_string(this->position.y) + std::to_string(this->age) + " " 
           + (this->food == LOADED ? "true" : "false") + "\n";
}

Defensor::Defensor(csquare position, unsigned age)
    : Ant(position), age(age) {
    square_add(position);
}

Ant* Defensor::data_validation(std::istringstream& data,
                               csquare anthill_position,
                               const unsigned& home) {
    Ant* defensor = nullptr;
    square position = {0, 0, sizeD, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age))
        std::cout << "reading error!" << std::endl;

    if(!square_validation(position)) return nullptr;

    if (square_superposition(position)) {
        square overlap = square_get_superposition(position);
        std::cout << message::defensor_overlap(position.x, position.y,
                                               overlap.x, overlap.y);
        return nullptr;
    }

    if (!square_contains(anthill_position, position)) {
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

Predator::Predator(csquare position, unsigned age)
    : Ant(position), age(age) {
    square_add(position);
}

Ant* Predator::data_validation(std::istringstream& data) {
    Ant* predator = nullptr;
    square position = {0, 0, sizeP, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age))
        std::cout << "reading error!" << std::endl;

    if(!square_validation(position)) return nullptr;

    if (square_superposition(position)) {
        std::cout << message::predator_overlap(position.x, position.y);
        return nullptr;
    }

    predator = new Predator(position, age);
    return predator;
}

std::string Predator::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
                + std::to_string(this->position.y) + " "
                + std::to_string(this->age) + "\n";
}
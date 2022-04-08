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

using namespace std;

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
        cout << message::generator_overlap(position.x, position.y, overlap.x,
                                           overlap.y);
        return nullptr;
    }

    if (!square_contains(anthill_position, position)) {
        cout << message::generator_not_within_home(position.x, position.y, home);
        return nullptr;
    }

    generator = new Generator(position);
    return generator;
}

Collector::Collector(csquare position, unsigned age, Etat_collector food)
    : Ant(position), age(age), food(food) {
    square_add(position);
}

Ant* Collector::data_validation(istringstream& data) {
    Ant* collector = nullptr;
    square position = {0, 0, sizeC, 1};
    unsigned age;
    string food_state;
    Etat_collector food;
    if (!(data >> position.x >> position.y >> age >> food_state))
          cout << "reading error!" << endl;
    food = food_state == "true" ? LOADED : EMPTY;

    if(!square_validation(position)) return nullptr;

    if (square_superposition(position)) {
        square overlap = square_get_superposition(position);
        cout << message::collector_overlap(position.x, position.y,
                                           overlap.x, overlap.y);
        return nullptr;
    }

    collector = new Collector(position, age, food);
    return collector;
}

Defensor::Defensor(csquare position, unsigned age)
    : Ant(position), age(age) {
    square_add(position);
}

Ant* Defensor::data_validation(istringstream& data,
                               csquare anthill_position,
                               const unsigned& home) {
    Ant* defensor = nullptr;
    square position = {0, 0, sizeD, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age)) cout << "reading error!" << endl;

    if(!square_validation(position)) return nullptr;

    if (square_superposition(position)) {
        square overlap = square_get_superposition(position);
        cout << message::defensor_overlap(position.x, position.y,
                                          overlap.x, overlap.y);
        return nullptr;
    }

    if (!square_contains(anthill_position, position)) {
        cout << message::defensor_not_within_home(position.x, position.y, home);
        return nullptr;
    }

    defensor = new Defensor(position, age);
    return defensor;
}

Predator::Predator(csquare position, unsigned age)
    : Ant(position), age(age) {
    square_add(position);
}

Ant* Predator::data_validation(istringstream& data) {
    Ant* predator = nullptr;
    square position = {0, 0, sizeP, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age)) cout << "reading error!" << endl;

    if(!square_validation(position)) return nullptr;

    if (square_superposition(position)) {
        cout << message::predator_overlap(position.x, position.y);
        return nullptr;
    }

    predator = new Predator(position, age);
    return predator;
}
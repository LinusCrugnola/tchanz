/******************************************************************************!
* @file     ants.cc
* @author   Léo Brückl <leo.bruckl@epfll.ch>            10 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include <iostream>

#include "ants.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

using namespace std;

//These functions verify the data of every ant. An ant must fit in the grid
//A generator ant must be in an given anthill

Ant* Generator::data_validation(unsigned xg, unsigned yg, 
                                    const square& anthill_position, 
                                    const unsigned& home){
    Ant* generator = nullptr;
    square position = {xg, yg, sizeG, 1};

    square_validation(position); // throws error if position invalid

    if(square_superposition(position)){
        square overlap = square_get_superposition(position);
        cout << message::generator_overlap(position.x, position.y, overlap.x, 
                                            overlap.y);
        exit(EXIT_FAILURE);
    }

    if(!square_contains(anthill_position, position)){
        cout << message::generator_not_within_home(position.x, position.y, home);
        exit(EXIT_FAILURE);
    }

    // Generate ant
    generator = new Generator(position);
    return generator;
}

Ant* Collector::data_validation(istringstream& data){
    Ant* collector = nullptr;
    square position = {0, 0, sizeC, 1};
    unsigned age;
    string food_state;
    Etat_collector food;
    if(!(data >> position.x >> position.y >> age >> food_state)) cout << "reading error!" << endl;
    food = food_state == "true" ? LOADED : EMPTY;

    square_validation(position); // throws error if position invalid

    if(square_superposition(position)){
        square overlap = square_get_superposition(position);
        cout << message::collector_overlap(position.x, position.y, 
                                            overlap.x, overlap.y);
        exit(EXIT_FAILURE);
    }

    // Generate ant
    collector = new Collector(position, age, food);
    return collector;
}

Ant* Defensor::data_validation(istringstream& data, 
                                const square& anthill_position, 
                                const unsigned& home){
    Ant* defensor = nullptr;
    square position = {0, 0, sizeD, 1};
    unsigned age;
    if(!(data >> position.x >> position.y >> age)) cout << "reading error!" << endl;

    square_validation(position); // throws error if position invalid

    if(square_superposition(position)){
        square overlap = square_get_superposition(position);
        cout << message::defensor_overlap(position.x, position.y, 
                                        overlap.x, overlap.y);
        exit(EXIT_FAILURE);
    }

    if(!square_contains(anthill_position, position)){
        cout << message::defensor_not_within_home(position.x, position.y, home);
        exit(EXIT_FAILURE);
    }

    // Generate ant
    defensor = new Defensor(position, age);
    return defensor;
}

Ant* Predator::data_validation(istringstream& data){
    Ant* predator = nullptr;
    square position = {0, 0, sizeP, 1};
    unsigned age;
    if(!(data >> position.x >> position.y >> age)) cout << "reading error!" << endl;

    square_validation(position); // throws error if position invalid

    if(square_superposition(position)){
        cout << message::predator_overlap(position.x, position.y);
        exit(EXIT_FAILURE);
    }

    // Generate ant
    predator = new Predator(position, age);
    return predator;
}
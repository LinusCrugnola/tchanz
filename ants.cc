/****************************************************************!
 \file     ants.cc
 \author   Léo Brückl, Linus Crugnola
 \date     31.03.2022
 \brief    ants implementation
*****************************************************************/

#include <iostream>

#include "ants.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

using namespace std;

Generator Generator::data_validation(unsigned xg, unsigned yg, const square& anthill_position, const unsigned& home){
    square position = {xg, yg, sizeG, 1};
    square_validation(position); // throws error if position invalid
    if(square_superposition(position)){
        square overlap = square_get_superposition(position);
        cout << message::generator_overlap(position.x, position.y, overlap.x, overlap.y) ;
        exit(EXIT_FAILURE);
    }
    if(!square_contains(anthill_position, position)){
        cout << message::generator_not_within_home(position.x, position.y, home) ;
        exit(EXIT_FAILURE);
    }
    // Generate ant
    Generator generator(position);
    return generator;
}

Collector Collector::data_validation(istringstream& data){
    square position = {0, 0, sizeC, 1};
    unsigned age;
    string food_state;
    Etat_collector food;
    if(!(data >> position.x >> position.y >> age >> food_state)) cout << "reading error!" << endl;
    food = food_state == "true" ? LOADED : EMPTY;
    square_validation(position); // throws error if position invalid
    if(square_superposition(position)){
        square overlap = square_get_superposition(position);
        cout << message::collector_overlap(position.x, position.y, overlap.x, overlap.y) ;
        exit(EXIT_FAILURE);
    }
    // Generate ant
    Collector collector(position, age, food);
    return collector;
}

Defensor Defensor::data_validation(istringstream& data, const square& anthill_position, const unsigned& home){
    square position = {0, 0, sizeD, 1};
    unsigned age;
    if(!(data >> position.x >> position.y >> age)) cout << "reading error!" << endl;
    square_validation(position); // throws error if position invalid
    if(square_superposition(position)){
        square overlap = square_get_superposition(position);
        cout << message::defensor_overlap(position.x, position.y, overlap.x, overlap.y) ;
        exit(EXIT_FAILURE);
    }
    if(!square_contains(anthill_position, position)){
        cout << message::defensor_not_within_home(position.x, position.y, home) ;
        exit(EXIT_FAILURE);
    }
    // Generate ant
    Defensor defensor(position, age);
    return defensor;
}

Predator Predator::data_validation(istringstream& data){
    square position = {0, 0, sizeP, 1};
    unsigned age;
    if(!(data >> position.x >> position.y >> age)) cout << "reading error!" << endl;
    square_validation(position); // throws error if position invalid
    if(square_superposition(position)){
        cout << message::predator_overlap(position.x, position.y) ;
        exit(EXIT_FAILURE);
    }
    // Generate ant
    Predator predator(position, age);
    return predator;
}
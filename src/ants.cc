/****************************************************************!
 \file     ants.cc
 \author   Léo Brückl, Linus Crugnola
 \date     25.03.2022
 \brief    ants implementation
*****************************************************************/
 
#include "ants.h"
#include "squarecell.h"
#include "constantes.h"

using namespace std;

Generator Generator::data_validation(istringstream data){
    //TODO: think about this (validation steps)
    square position = {0, 0, sizeG, 0}; //are ants centered?
    if(!(data >> position.x >> position.y >> age)) exit(EXIT_FAILURE);
    square_validation(position);
    square_superposition(position); //functions throw error if position invalid
    // Generate ant
}

Collector Collector::data_validation(istringstream data){
    square position = {0, 0, sizeC, 0}; //are ants centered?
    unsigned age;
    Etat_collector food;
    if(!(data >> position.x >> position.y >> age >> food)) exit(EXIT_FAILURE);
    square_validation(position);
    square_superposition(position); //functions throw error if position invalid
    //TODO: check if it is in anthill
    // Generate ant
    Collector collector(position, age, food);
    return collector;
}

Defensor Defensor::data_validation(istringstream data){
    square position = {0, 0, sizeD, 0}; //are ants centered?
    unsigned age;
    if(!(data >> position.x >> position.y >> age)) exit(EXIT_FAILURE);
    square_validation(position);
    square_superposition(position); //functions throw error if position invalid
    //TODO: check if it is in anthill
    // Generate ant
    Defensor defensor(position, age);
    return defensor;
}

Predator Predator::data_validation(istringstream data){
    square position = {0, 0, sizeP, 0}; //are ants centered?
    unsigned age;
    if(!(data >> position.x >> position.y >> age)) exit(EXIT_FAILURE);
    square_validation(position);
    square_superposition(position); //functions throw error if position invalid
    //TODO: check if it is in anthill
    // Generate ant
    Predator predator(position, age);
    return predator;
}
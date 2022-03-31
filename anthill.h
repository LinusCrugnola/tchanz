/******************************************************************************!
* @file     anthill.h
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/

#ifndef ANTHILL_H
#define ANTHILL_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ants.h"
#include "error_squarecell.h"
#include "squarecell.h"

class Anthill {
private:
    square position;
    unsigned total_food;
    unsigned nbC, nbD, nbP;

    std::vector<Generator> generator;
    std::vector<Collector> collectors;
    std::vector<Defensor> defensors;
    std::vector<Predator> predators;

public:
    square get_position() const {
        return position;
    }
    //Verification of an anthill's data. If it fits in the grid AND if it overlaps 
    //with another anthill or entity
    static Anthill anthill_validation(std::istringstream& data,
                                      std::vector<Anthill> anthills, unsigned home);
    
    unsigned anthill_get_ants();
    //Function which verifies if an ant fits in the grid. Then it is put in 
    //the respected class list of an anthill
    void ant_validation(std::istringstream& data, unsigned home);

    Anthill(square position, unsigned total_food, unsigned nbC, unsigned nbD,
            unsigned nbP, unsigned xg, unsigned yg, unsigned home);
};

#endif
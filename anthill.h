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

    std::vector<Ant*> ants;

public:
    square get_position() const {
        return position;
    }

    /**
     * @brief Verification of an anthill's data. 
     * If it fits in the grid AND if it overlaps with another anthill or entity
     */
    static Anthill* anthill_validation(std::istringstream& data,
                                     const std::vector<Anthill*>& hills_existing, 
                                     const unsigned& home);

    /**
     * @brief This function returns the number of ants in anthill
     */
    unsigned anthill_get_ants();

    /**
     * @brief Function which verifies if an ant fits in the grid. 
     * Then it is put in a class list of an anthill 
     */
    void ant_validation(std::istringstream& data, unsigned home);

    /**
     * @brief Construct a new Anthill object 
     */
    Anthill(square position, unsigned total_food, unsigned nbC, unsigned nbD,
            unsigned nbP, unsigned xg, unsigned yg, unsigned home);
};

#endif
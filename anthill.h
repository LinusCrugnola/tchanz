/******************************************************************************!
* @file     anthill.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#ifndef ANTHILL_H
#define ANTHILL_H

#include <sstream>
#include <vector>

#include "ants.h"
#include "squarecell.h"

/**
 * @class Anthill
 */
class Anthill {
private:
    square position;
    unsigned total_food;
    unsigned nbC, nbD, nbP;

    /**
     * @brief vector of ants that belong to hill
     */
    std::vector<Ant*> ants;

public:
    square get_position() const {
        return position;
    }

    /**
     * @brief Verification of an anthill's data. 
     * Test if hill fits in the grid AND doesnt overlaps with an existing anthill
     * @param data input stream, existing anthills and number of home (starts at 0)
     * @returns Pointer on new anthill object
     */
    static Anthill* anthill_validation(std::istringstream& data,
                                     const std::vector<Anthill*>& hills_existing, 
                                     const unsigned& home);

    /**
     * @brief This function returns the number of ants in anthill
     */
    unsigned anthill_get_ants();

    /**
     * @brief Function which verifies if an ant fits in the grid and doesn't overlap
     * with another entity
     * @param data input stream and number of home (starts at 0)
     * @result if ant is valid, it is added to ants attribute of this hill
     */
    void ant_validation(std::istringstream& data, unsigned home);

    /**
     * @brief Construct a new Anthill object
     * 
     * @param position 2D coordinates (center) and side length
     * @param total_food 
     * @param nbC number of collector ants
     * @param nbD number of defensor ants
     * @param nbP number of predator ants
     * @param xg x coordinate of generator
     * @param yg y coordinate of generator
     * @param home number of hill (starts at 0)
     */
    Anthill(square position, unsigned total_food, unsigned nbC, unsigned nbD,
            unsigned nbP, unsigned xg, unsigned yg, unsigned home);
};

#endif
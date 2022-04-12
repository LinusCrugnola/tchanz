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
#include "generator.h"
#include "collector.h"
#include "defensor.h"
#include "predator.h"
#include "squarecell.h"

typedef const unsigned& cunsigned;

/**
 * @class Anthill
 * 
 * @brief Anthill contains different ants
 */
class Anthill {
private:
    scl::square position;
    unsigned total_food;
    unsigned nbC, nbD, nbP;

    /**
     * @brief vector of ants that belong to hill
     */
    std::vector<Ant*> ants;

public:
    scl::square get_position() const {return position;}

    /**
     * @brief Verification of an anthill's data. 
     * Test if hill fits in the grid AND doesnt overlaps with an existing anthill
     * 
     * @param data input stream
     * @param hills_existing anthills that already exist 
     * @param home number of current hill (starts at 0)
     * 
     * @returns Pointer on new anthill object, null if invalid
     */
    static Anthill* anthill_validation(std::istringstream& data,
                                       std::vector<Anthill*>& hills_existing, 
                                       cunsigned home);

    /**
     * @brief This function returns the number of ants in anthill
     */
    unsigned anthill_get_ants() const;

    /**
     * @brief Function which verifies if an ant fits in the grid and doesn't overlap
     * with another entity
     * 
     * @param data input stream
     * @param home number of current hill (starts at 0)
     * 
     * @result if ant is valid, it is added to ants attribute of the anthill
     */
    bool ant_validation(std::istringstream& data, cunsigned home);

    /**
     * @brief Get the configfile data of the hill and its ants
     * 
     * @return std::string 
     */
    std::string get_filedata(unsigned home);

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
    Anthill(scl::csquare position, cunsigned total_food, cunsigned nbC, cunsigned nbD,
            cunsigned nbP);

    /**
     * @brief Destroy the Anthill object
     * 
     * @note destroys all ants of the hill and frees their squares in the grid
     */
    ~Anthill();
};

#endif
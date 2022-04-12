#ifndef GENERATOR_H
#define GENERATOR_H

#include <sstream>
#include <string>

#include "squarecell.h"
#include "constantes.h"
#include "ants.h"

class Ant;

/**
 * @class Generator
 * @brief Subclass of ant
 * 
 * @note Each anthill has a Generator that stays inside of the hill
 */
class Generator : public Ant {
public:

    /**
     * @brief validates that an ants position is inside the hill and it doesn't 
     * intersect with another entity
     * 
     * @param xg x coordinate of generator
     * @param yg y cooridinate of generator
     * @param anthill_position position of the parent anthill
     * @param home number of parent anthill (starts at 0)
     * 
     * @returns pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(scl::coord xg, scl::coord yg, scl::csquare 
                                anthill_position, const unsigned& home);

    /**
     * @brief get the configfile data of a generator
     * 
     * @return std::string with x and y coordinate
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Generator object
     * 
     * @param position 2D coordinates (center) and side length
     */
    Generator(scl::csquare position);
};

#endif
/******************************************************************************!
 * @file     ants.h
 * @author   Léo Brückl <leo.bruckl@epfl.ch> 
 *           Linus Crugnola <linus.crugnola@epfl.ch>
 * @version  1.0
 * @date     01.04.2022
 *******************************************************************************/

#ifndef ANTS_H
#define ANTS_H

#include <sstream>

#include "squarecell.h"
#include "constantes.h"

/**
 * @class Ant
 * @brief Base class of ants
 */
class Ant {
protected:
    scl::square position;

public:
    /**
     * @brief Construct a new Ant object
     * 
     * @param position 2D coordinates (center) and side length
     */
    Ant(scl::csquare position); 
    
    /**
     * @brief Get the configfile data of an ant object
     * 
     * @return std::string 
     */
    virtual std::string get_filedata() = 0;

    /**
     * @brief Destroy the Ant object
     * 
     * @note Frees the square occupied by the ant
     */
    virtual ~Ant();
};

#endif
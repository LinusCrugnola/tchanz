/******************************************************************************!
 * @file     ant.h
 * @author   Léo Brückl <leo.bruckl@epfl.ch> 
 *           Linus Crugnola <linus.crugnola@epfl.ch>
 * @version  2.0
 * @date     01.04.2022
 *******************************************************************************/

#ifndef ANT_H
#define ANT_H

#include <sstream>

#include "constantes.h"
#include "squarecell.h"

/**
 * @class Ant
 * @brief Base class of ants
 */
class Ant {
protected:
    /**
     * @brief position of the ant (square)
     */
    scl::square position;

    /**
     * @brief true if ant is dead
     */
    bool end_of_life;

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
     * @brief draw the ant on the gui canvas
     * 
     * @param color specifies the color of the ant (parent color)
     * 
     * @return true if no errors
     */
    virtual bool draw(graphic::color color) = 0;

    /**
     * @brief Destroy the Ant object
     * 
     * @note Frees the square occupied by the ant
     */
    virtual ~Ant();
};

#endif /* ANT_H */
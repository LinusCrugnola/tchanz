/******************************************************************************!
* @file     predator.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#ifndef PREDATOR_H
#define PREDATOR_H

#include <sstream>
#include <string>

#include "squarecell.h"
#include "constantes.h"
#include "ants.h"

class Ant;

/**
 * @class Predator
 * @brief Subclass of ant
 * 
 * @note At simulation initialization, predators must be inside the anthill
 * @note Preadator ants atack other anthills
 */
class Predator : public Ant {
private:
    unsigned age;

public:
    /**
     * @brief draw the predator ant
     * 
     * @remark draws a small square 
     * 
     * @param color specifies the color of the ant (parent color)
     * 
     * @return true if no errors
     */
    virtual bool draw(graphic::color color) override;

    /**
     * @brief validates that an ants position is inside the grid and it doesn't 
     * intersect with another entity
     * 
     * @param input data stream
     * 
     * @returns pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data);

    /**
     * @brief get the configfile data of a predator
     * 
     * @return std::string with coordinates and age
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Predator object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     */
    Predator(scl::csquare position, unsigned age);
};

#endif /* PREDATOR_H */

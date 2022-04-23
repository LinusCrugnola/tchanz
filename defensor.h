/******************************************************************************!
* @file     defensor.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#ifndef DEFENSOR_H
#define DEFENSOR_H

#include <sstream>
#include <string>

#include "squarecell.h"
#include "constantes.h"
#include "ants.h"

class Ant;

/**
 * @class Defensor
 * @brief Subclass of ant
 * 
 * @note Defensor ants defend the anthill
 */
class Defensor : public Ant {
private:
    unsigned age;

public:
    /**
     * @brief draw the defensor ant
     * 
     * @remark draws a square with a cross inside
     * 
     * @param color specifies the color of the ant (parent color)
     * 
     * @return true if no errors
     */
    virtual bool draw(graphic::color color) override;

    /**
     * @brief validates that an ants position is inside the hill and it doesn't 
     * intersect with another entity
     * 
     * @param input data stream, position and number of anthill
     * 
     * @returns pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data, scl::csquare 
                                anthill_position, const unsigned& home);

    /**
     * @brief get the configfile data of a defensor
     * 
     * @return std::string with coordinates and age
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Defensor object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     */
    Defensor(scl::csquare position, unsigned age);
};

#endif /* DEFENSOR_H */

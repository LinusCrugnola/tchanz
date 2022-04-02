/******************************************************************************!
 * @file     nutrition.h
 * @author   Léo Brückl <leo.bruckl@epfl.ch> 
 *           Linus Crugnola <linus.crugnola@epfl.ch>
 * @version  1.0
 * @date     01.04.2022
 *******************************************************************************/

#ifndef NUTRITION_H
#define NUTRITION_H

#include <sstream>

#include "squarecell.h"

/**
 * @class Nutrition
 * 
 * @brief Nutrition objects are points in the grid that can be collected by collector 
 * ants
 */
class Nutrition {
private:
    unsigned x, y;
    double val_food;

public:
    /**
     * @brief Verification if coordinates fit in the grid and if it has a distance
     * bigger than 1 from the border.
     * Also verifies if food overlaps with another entity.
     * 
     * @param data input string stream
     */
    static Nutrition* data_validation(std::istringstream& data);

    /**
     * @brief Construct a new Nutrition object
     */
    Nutrition(unsigned x_coor, unsigned y_coor);

    /**
     * @brief Destroy the Nutrition object
     * 
     * @note frees the square occupied by the object in the grid
     */
    ~Nutrition();
};

#endif
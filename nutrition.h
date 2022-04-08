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
#include <vector>

#include "squarecell.h"

/**
 * @brief Concrete type for storing nutrition data
 */
struct Food_data{
    square position;
    double val_food;
};

/**
 * @class Nutrition
 * 
 * @brief Nutrition is a container that handles all Nutrition elements in the grid
 */
class Nutrition {
private:
    /**
     * @brief Map of Food_data to store the nutrition elements
     */


public:
    /**
     * @brief Verification if coordinates fit in the grid and if it has a distance
     * bigger than 1 from the border.
     * Also verifies if food overlaps with another entity.
     * 
     * @param data input string stream
     */
    void add_element(std::istringstream& data);

    /**
     * @brief Construct a new Nutrition object
     */
    Nutrition();

    /**
     * @brief Destroy the Nutrition object
     */
    ~Nutrition();
};

#endif
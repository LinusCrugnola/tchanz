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
 * @class Nutrition
 * 
 * @brief Nutrition is a container that handles all Nutrition elements in the grid
 */
class Nutrition {
private:
    /**
     * @brief Vector of Food_data to store the nutrition elements
     * 
     * @remark TEMPORARY, for rendu 3 this could be changed to a unordered map 
     * (fast existance verification)
     */
    std::vector<scl::square> foods;

public:
    /**
     * @brief Verification if coordinates fit in the grid and if it has a distance
     * bigger than 1 from the border.
     * Also verifies if food overlaps with another entity.
     * 
     * @param data input string stream
     */
    bool add_element(std::istringstream& data);

    /**
     * @brief Get the total amount of food
     * 
     * @return unsigned int
     */
    unsigned get_nbF();

    /**
     * @brief draw all food elements on gui canvas
     * 
     * @return true if no errors
     */
    bool draw_all();

    /**
     * @brief Get position data of all nutrition elements in configfile format
     * 
     * @return std::string 
     */
    std::string get_filedata();

    /**
     * @brief delete all food objects
     * 
     * @note deletes squares from grid
     */
    void clear();

    /**
     * @brief Construct a new Nutrition object
     */
    Nutrition() {};

    /**
     * @brief Destroy the Nutrition object
     * 
     * @note free the grid
     */
    ~Nutrition();
};

#endif /* NUTRITION_H */
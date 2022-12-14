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
     */
    std::vector<scl::square> foods;

public:
    /**
     * @brief Get the nearest food element
     * 
     * @param pos_collector position of the collector ant
     * @return scl::square position of the nearest food element
     */
    scl::square get_nearest(scl::csquare pos_collector);
 
    /**
     * @brief Verification if coordinates fit in the grid and if it has a distance
     * bigger than 1 from the border.
     * Also verifies if food overlaps with another entity.
     * 
     * @param data input string stream
     */
    bool add_element(std::istringstream& data);

    /**
     * @brief Add a new food element if valid
     * 
     * @param x coordinate of the food
     * @param y coordinate of the food
     * @return true if element was added
     */
    bool add_element(unsigned x, unsigned y);

    /**
     * @brief delete a food element
     * 
     * @param position of the element
     * @return true if element could be deleted
     */
    bool delete_element(scl::csquare position);

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
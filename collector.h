/******************************************************************************!
* @file     collector.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <sstream>
#include <string>

#include "squarecell.h"
#include "constantes.h"
#include "ants.h"

class Ant;

/**
 * @class Collector
 * @brief Subclass of ant
 * 
 * @note Collector ants search and carry food
 */
class Collector : public Ant {
private:
    /**
     * @brief age of the ant
     */
    unsigned age;

    /**
     * @brief state of the collector ant
     * @remark empty => no food, loaded => carrying a food item
     */
    Etat_collector food_state;

public:
    /**
     * @brief draw the collector ant
     * 
     * @remark draws a square with diagonals
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
     * @return pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data);

    /**
     * @brief get the configfile data of a collector
     * 
     * @return std::string with coordinates, age and state
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Collector object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     * @param food a collector can initially be empty or loaded
     */
    Collector(scl::csquare position, unsigned age, Etat_collector food);
};

#endif
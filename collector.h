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
#include "ant.h"
#include "nutrition.h"

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

    /**
     * @brief pointer on the nutrition object stored in simulation
     */
    Nutrition* nutrition;

    /**
     * @brief count the superpositions on a given path with
     * 
     * @param prim first direction
     * @param steps1 number of steps following prim
     * @param sec second direction
     * @param steps2 number of steps following sec
     * @return unsigned number of superpositions
     */
    unsigned count_superpos(scl::vector prim, unsigned steps1, 
                            scl::vector sec, unsigned steps2);

    /**
     * @brief verify if the given move can be done
     * 
     * @param step the step to verify
     * @return true if valid & move
     */
    bool verify_position(scl::cvector step);

    /**
     * @brief Get the next step for a given target
     * 
     * @param target 
     * @return scl::vector next step
     */
    scl::vector get_step(scl::csquare target);

public:
    /**
     * @brief move the collector ant
     * 
     * @param hill_pos 
     * @return true if no errors
     */
    virtual bool action(scl::csquare hill_pos, bool free) override;

    bool control_path(scl::csquare food_pos);

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
     * @brief return if the collector is loaded
     * 
     * @return bool 
     */
    virtual bool loaded() const override;
    
    /**
     * @brief validates that an ants position is inside the grid and it doesn't 
     * intersect with another entity
     * 
     * @param input data stream
     * @param nutrition pointer on the food object
     * @param hill_index index of the parent anthill
     * 
     * @return pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data, Nutrition* nutrition, 
                                unsigned hill_index);

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
     * @param nutrition pointer on the nutrition object
     * @param hill_index index of the parent anthill
     */
    Collector(scl::csquare position, unsigned age, Etat_collector food, 
              Nutrition* nutrition, unsigned hill_index);

    /**
     * @brief Destroy the Collector object
     * @remark drops the food item if loaded
     */
    ~Collector() override;
};

#endif /* COLLECTOR_H */
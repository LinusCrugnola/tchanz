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
#include "ant.h"

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
    /**
     * @brief age of the ant
     */
    unsigned age;

    /**
     * @brief kill all ants that touch the predator
     */
    void kill_touching();

    /**
     * @brief true if collector is heading to his home anthill
     */
    bool heading_home;

    /**
     * @brief Set the target for the predator ant
     * 
     * @param hill_pos position of the anthill
     * @param free state of the anthill
     * @return scl::square target position
     */
    scl::square set_target(scl::square hill_pos, bool free);

    /**
     * @brief move the predator ant in the direction of the target
     * 
     * @param target scl::square
     */
    bool move(scl::csquare target);

public:
    /**
     * @brief move the predator ant
     * 
     * @param hill_pos position of the hill
     * @param free indicates if hill can grow
     * @return true if no errors
     */
    virtual bool action(scl::csquare hill_pos, bool free) override;

    /**
     * @brief draw the predator ant
     * @remark draws a small square 
     * 
     * @param color specifies the color of the ant (parent color)
     * @return true if no errors
     */
    virtual bool draw(graphic::color color) override;

    /**
     * @brief validates that an ants position is inside the grid and it doesn't 
     * intersect with another entity
     * 
     * @param data input stream
     * @param hill_index index of the parent anthill
     * 
     * @return pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data, unsigned hill_index);

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
     * @param hill_index index of the parent anthill
     */
    Predator(scl::csquare position, unsigned age, unsigned hill_index);
};

#endif /* PREDATOR_H */

/******************************************************************************!
* @file     generator.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#ifndef GENERATOR_H
#define GENERATOR_H

#include <sstream>
#include <string>

#include "squarecell.h"
#include "constantes.h"
#include "ant.h"

class Ant;

/**
 * @class Generator
 * @brief Subclass of ant
 * 
 * @note Each anthill has a Generator that stays inside of the hill
 */
class Generator : public Ant {
private:
    /**
     * @brief total food of the clan
     */
    double total_food;

    /**
     * @brief total ants present in hill
     */
    unsigned total_ants;

    /**
     * @brief move method of the generator
     * @details moves to the middle of the hill if possible
     * 
     * @param hill_pos position of the anthill
     */
    bool move(scl::csquare hill_pos);

    /**
     * @brief verify if a position is valid
     * 
     * @param new_pos position to verify
     * @param hill_pos position of the anthill
     * @return true if position is valid
     */
    bool verify_position(scl::csquare new_pos, scl::csquare hill_pos);

public:
    /**
     * @brief move the generator ant
     * 
     * @param hill_pos 
     * @return true if no errors
     */
    virtual bool action(scl::csquare hill_pos, bool free) override;

    /**
     * @brief draw the generator ant
     * 
     * @remark draws a filled square
     * 
     * @param color specifies the color of the ant (parent color)
     * 
     * @return true if no errors
     */
    virtual bool draw(graphic::color color) override;

    /**
     * @brief Get the total food
     * 
     * @return unsigned
     */
    double get_total_food() const {return this->total_food;}

    /**
     * @brief add new food to total_food
     * 
     * @param food number of new food items
     */
    void add_food(unsigned food);

    /**
     * @brief Set the total amount of ants
     * 
     * @param total
     */
    void set_total_ants(unsigned total);

    /**
     * @brief validates that an ants position is inside the hill and it doesn't 
     * intersect with another entity
     * 
     * @param xg x coordinate of generator
     * @param yg y cooridinate of generator
     * @param anthill_position position of the parent anthill
     * @param home number of parent anthill (starts at 0)
     * @param total_food initial quantity of foods stored in hill
     * 
     * @return pointer to new ant object, null if position is invalid
     */
    static Generator* data_validation(scl::coord xg, scl::coord yg, scl::csquare 
                                      anthill_position, const unsigned& home, 
                                      unsigned total_food);

    /**
     * @brief get the configfile data of a generator
     * 
     * @return std::string with x and y coordinate
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Generator object
     * 
     * @param position 2D coordinates (center) and side length
     * @param total_food initial quantity of food stored in hill
     * @param hill_index index of the parent anthill
     */
    Generator(scl::csquare position, double total_food, unsigned hill_index);
};

#endif /* GENERATOR_H */
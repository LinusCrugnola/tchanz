/******************************************************************************!
 * @file     ant.h
 * @author   Léo Brückl <leo.bruckl@epfl.ch> 
 *           Linus Crugnola <linus.crugnola@epfl.ch>
 * @version  2.0
 * @date     01.04.2022
 *******************************************************************************/

#ifndef ANT_H
#define ANT_H

#include <sstream>
#include <vector>

#include "constantes.h"
#include "squarecell.h"

/**
 * @class Ant
 * @brief Base class of ants
 */
class Ant {
protected:
    /**
     * @brief position of the ant (square)
     */
    scl::square position;

    /**
     * @brief true if ant is dead
     */
    bool end_of_life;

    /**
     * @brief index of the parent anthill
     */
    unsigned hill_index;

    static std::vector<std::vector<Ant*>> predatables;

public:
    /**
     * @brief Construct a new Ant object
     * 
     * @param position 2D coordinates (center) and side length
     * @param hill_index index of the parent anthill
     * @param predatable indicates if ant can be targeted by a predator ant
     */
    Ant(scl::csquare position, unsigned hill_index, bool predatable);

    /**
     * @brief Get the position of the ant
     * 
     * @return scl::square 
     */
    scl::square get_position() const { return this->position; }

    /**
     * @brief Get the hill index of the ant
     * 
     * @return unsinged 
     */
    unsigned get_hill() const { return this->hill_index; }

    /**
     * @brief check if ant is dead
     * 
     * @return true if ant is dead
     */
    bool is_dead() const { return this->end_of_life; }

    /**
     * @brief set end_of life to true
     */
    void kill();

    /**
     * @brief action of the ant (move)
     * 
     * @param hill_pos position of the hill
     * @return true if no errors
     */
    virtual bool action(scl::csquare hill_pos, bool free) = 0;

    /**
     * @brief returns if the ant carries a food item
     * 
     * @return bool
     */
    virtual bool loaded() const { return false; }

    /**
     * @brief Get the configfile data of an ant object
     * 
     * @return std::string 
     */
    virtual std::string get_filedata() = 0;

    /**
     * @brief draw the ant on the gui canvas
     * 
     * @param color specifies the color of the ant (parent color)
     * 
     * @return true if no errors
     */
    virtual bool draw(graphic::color color) = 0;

    /**
     * @brief Destroy the Ant object
     * 
     * @note Frees the square occupied by the ant
     */
    virtual ~Ant();
};

#endif /* ANT_H */
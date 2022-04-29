/******************************************************************************!
* @file     anthill.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#ifndef ANTHILL_H
#define ANTHILL_H

#include <sstream>
#include <vector>
#include <string>

#include "ants.h"
#include "generator.h"
#include "collector.h"
#include "defensor.h"
#include "predator.h"
#include "squarecell.h"

typedef const unsigned& cunsigned;

/**
 * @class Anthill
 * 
 * @brief Anthill contains different ants
 */
class Anthill {
private:
    /**
     * @brief position of the hill (square)
     */
    scl::square position;

    /**
     * @brief total food stocked in the hill
     */
    double total_food;
    //TODO: check consequences

    /**
     * @brief number of collector, defensor and predator ants belonging to the hill
     */
    unsigned nbC, nbD, nbP;

    /**
     * @brief color of the hill and all it's children
     */
    graphic::color color;

    /**
     * @brief state of the hill
     * 
     * @details free if the hill can grow in all directions, constrained if growth only in 
     * one direction.
     * 
     */
    Etat_fourmiliere anthill_state;

    /**
     * @brief true if clan is dead
     */
    bool end_of_klan;

    /**
     * @brief indicates if the hill is highlighted
     */
    bool highlight;

    /**
     * @brief vector of ants that belong to hill
     */
    std::vector<Ant*> ants;

public:
    /**
     * @brief Get the position of the anthill
     * 
     * @return scl::square 
     */
    scl::square get_position() const {return position;}

    /**
     * @brief highlight anthill (fill with transparent color)
     */
    void set_highlight();

    /**
     * @brief delete the highlight on anthill
     * 
     */
    void delete_highlight();

    /**
     * @brief draw the anthill on the gui canvas
     * 
     * @return true if no errors
     */
    bool draw_hill();

    /**
     * @brief draw all of the hills ants on the gui canvas
     * 
     * @return true if no errors
     */
    bool draw_ants();

    /**
     * @brief Verification of an anthill's data. 
     * Test if hill fits in the grid AND doesnt overlaps with an existing anthill
     * 
     * @param data input stream
     * @param hills_existing anthills that already exist 
     * @param home number of current hill (starts at 0)
     * 
     * @return Pointer on new anthill object, null if invalid
     */
    static Anthill* anthill_validation(std::istringstream& data,
                                       std::vector<Anthill*>& hills_existing, 
                                       cunsigned home);

    /**
     * @brief This function returns the number of ants in anthill
     */
    unsigned anthill_get_ants() const;

    /**
     * @brief Function which verifies if an ant fits in the grid and doesn't overlap
     * with another entity
     * 
     * @param data input stream
     * @param home number of current hill (starts at 0)
     * 
     * @result if ant is valid, it is added to ants attribute of the anthill
     */
    bool ant_validation(std::istringstream& data, cunsigned home);

    /**
     * @brief Get the configfile data of the hill and its ants
     * 
     * @return std::string 
     */
    std::string get_filedata(unsigned home);

    /**
     * @brief Get the info of the anthill that is displayed in GUI
     * 
     * @return std::string 
     */
    std::string get_info();

    /**
     * @brief Construct a new Anthill object
     * 
     * @param position 2D coordinates (center) and side length
     * @param total_food 
     * @param nbC number of collector ants
     * @param nbD number of defensor ants
     * @param nbP number of predator ants
     * @param xg x coordinate of generator
     * @param yg y coordinate of generator
     * @param home number of hill (starts at 0)
     */
    Anthill(scl::csquare position, cunsigned total_food, cunsigned nbC, cunsigned nbD,
            cunsigned nbP);

    /**
     * @brief Destroy the Anthill object
     * 
     * @note destroys all ants of the hill and frees their squares in the grid
     */
    ~Anthill();
};

#endif
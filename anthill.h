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
#include <random>

#include "ant.h"
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
     * @details FREE if the hill can grow, CONSTRAINED if the hill cann't grow
     */
    Etat_fourmiliere anthill_state;

    /**
     * @brief true if clan is dead
     */
    bool end_of_klan;

    /**
     * @brief indicates if the hill is highlight
     */
    bool highlight;

    /**
     * @brief generator ant of the hill
     */
    Generator* generator;

    /**
     * @brief vector of ants that belong to the hill
     */
    std::vector<Ant*> ants;

    /**
     * @brief index of the anthill (each hill has an unique index)
     */
    static unsigned anthill_count;
    unsigned index;

    /**
     * @brief set a new anthill position if the amount of ants changed
     * 
     * @param position new position
     * @param hills the other hills existing
     * 
     * @return true if the position could be changed
     */
    bool update_position(scl::csquare new_position, std::vector<Anthill*>& hills);

public:
    /**
     * @brief Get the position of the anthill
     * 
     * @return scl::square 
     */
    scl::square get_position() const {return position;}

    /**
     * @brief actions the generator ant
     * 
     * @param engine random engine for probability calc
     * @param food pointer on food object
     * 
     * @return true if generator died
     */
    bool generator_action(std::default_random_engine* engine, Nutrition* food);

    /**
     * @brief executes Ant::action of the other ants of the hill
     * 
     * @return true if no errors
     */
    bool ants_action() const;

    /**
     * @brief unload all collectors that are in contact with the hill
     * 
     * @return unsigned nuber of new foods
     */
    unsigned get_new_food() const;

    /**
     * @brief Create a new ant if there is space in the anthill
     * @remark creation probabilities in @file constants.h
     * 
     * @param food pointer on the nutrition object
     * 
     * @return true if ant could be created
     */
    bool create_ant(Nutrition* food);

    /**
     * @brief check if anthill is dead
     * 
     * @return true if anthill is dead
     */
    bool is_dead() const {return this->end_of_klan;}

    /**
     * @brief highlight anthill (fill with transparent color)
     */
    void set_highlight();

    /**
     * @brief delete the highlight on anthill
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
     * @brief removes all dead ants from the hill
     */
    void remove_dead_ants();

    /**
     * @brief Verification of an anthill's data. 
     * Test if hill fits in the grid AND doesnt overlap with an existing anthill
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
     * @brief get the number of ants in anthill
     * 
     * @return unsigned
     */
    unsigned get_ants() const;

    /**
     * @brief Function which verifies if an ant fits in the grid and doesn't overlap
     * with another entity
     * 
     * @param data input stream
     * @param home number of current hill (starts at 0)
     * @param nutrition pointer on food object
     * 
     * @result if ant is valid, it is added to ants attribute of the anthill
     */
    bool ant_validation(std::istringstream& data, cunsigned home, 
                        Nutrition* nutrition);

    /**
     * @brief Get the configfile data of the hill and its ants
     * 
     * @param home index of the home anthill
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
     * @brief verifies if the anthill can grow and updates its size if possible
     * @remark sets anthill_state to constrained if no growth possible
     * 
     * @param hills the other existing anthills
     * 
     * @return true if it could grow
     */
    bool check_growth(std::vector<Anthill*>& hills);

    /**
     * @brief Construct a new Anthill object
     * 
     * @param position 2D coordinates (center) and side length
     * @param nbC number of collector ants
     * @param nbD number of defensor ants
     * @param nbP number of predator ants
     */
    Anthill(scl::csquare position, cunsigned nbC, cunsigned nbD, cunsigned nbP);

    /**
     * @brief Destroy the Anthill object
     * 
     * @note destroys all ants of the hill and frees their squares in the grid
     */
    ~Anthill();
};

#endif /* ANTHILL_H */
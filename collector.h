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
     * @brief determines if the collector can drop his nutrition on the next 
     * move (touched anthill)
     */
    bool unload_next_move;

    /**
     * @brief pointer on the nutrition object stored in simulation
     */
    Nutrition* nutrition;

    /**
     * @brief count the superpositions on a given path with
     * 
     * @param path to step through
     * @param deviation @ref to inscribe an eventual deviation of the path
     * @return unsigned number of superpositions
     */
    unsigned count_superpos(scl::path path, unsigned& deviation);

    /**
     * @brief Get the step count first superposition
     * 
     * @param path to step through
     * @param deviation to inscribed deviation
     * @return unsigned step count
     */
    unsigned get_first_superpos(scl::path path, unsigned deviation);

    /**
     * @brief verify if the given move can be done
     * 
     * @param step the step to verify
     * @param target food item the collector is heading to
     * @param chasing determines if the collector is chasing a foood item
     * @return true if valid & move could be done
     */
    bool verify_position(scl::cvector step, scl::csquare target, bool chasing);

    /**
     * @brief Get the next step for a given target
     * @remark compares the two permutations of path
     * 
     * @param path to the target
     * @return scl::vector next step
     */
    scl::vector get_step(scl::path path);

    /**
     * @brief Get the best path to the target
     * 
     * @param target food object
     * @return scl::path 
     */
    scl::path get_path(scl::csquare target);

    /**
     * @brief leave the anthill on the fastest possible way
     * @remark if ambiguity leave in the direction of the center of the map
     * 
     * @param hill_pos position of the home
     */
    bool leave_home(scl::csquare hill_pos);

    /**
     * @brief try to move in every direction
     * @remark if ant is blocked it does this
     */
    bool move_unblock();

public:
    /**
     * @brief move the collector ant
     * 
     * @param hill_pos position of the anthill
     * @param free indicates if the anthill can grow
     * @return true if no errors
     */
    virtual bool action(scl::csquare hill_pos, bool free) override;

    /**
     * @brief draw the collector ant
     * @remark draws a square with diagonals
     * 
     * @param color specifies the color of the ant (parent color)
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
     * @brief validate configfile data and construct ant if valid
     * 
     * @param input data stream
     * @param nutrition pointer on the food object
     * @param hill_index index of the parent anthill
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
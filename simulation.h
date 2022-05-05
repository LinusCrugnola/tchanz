/******************************************************************************!
* @file     simulation.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include <random>

#include "anthill.h"
#include "nutrition.h"

/**
 * @class simulation
 * 
 * @brief Class that handles the entities
 */
class Simulation {
private:
    /**
     * @brief Anthill instances 
     */
    std::vector<Anthill*> anthill;

    /**
     * @brief Nutrition object
     */
    Nutrition food;

    /**
     * @brief random number generation objects
     */
    std::default_random_engine* rand_engine;
    std::bernoulli_distribution rand_bool;
    std::uniform_int_distribution<unsigned> rand_int;

    /**
     * @brief Distribute one line of the configfile
     * 
     * @param line string of one line
     * 
     * @return true if no error occured while reading the line
     */
    bool handle_line(const std::string& line);

    /**
     * @brief Get the header for a configfile with timestamp
     * 
     * @return std::string 
     */
    std::string get_fileheader();

public:
    /**
     * @brief udpates the simulation (1x)
     * 
     * @return true if no errors
     */
    bool update();

    /**
     * @brief Get the total food existing in the world
     * 
     * @return unsigned int
     */
    unsigned get_nbF();

    /**
     * @brief Get the info of the next anthill
     * 
     * @param reverse order of access
     * @param reset reset the info to initial state
     * @return anthill_info struct
     */
    std::string get_next_anthill_info(bool reverse, bool reset = false);

    /**
     * @brief draw the current state of the simulation on the gui canvas
     * 
     * @return true if no errors
     */
    bool draw_current_state();

    /**
     * @brief Read the configfile
     * 
     * @param filename name of the file to read
     * 
     * @return true if everything could be initialized
     */
    bool read_configfile(const std::string& filename);

    /**
     * @brief Store the actual state of the simulation in a configfile
     */
    void write_configfile(const std::string& filename);

    /**
     * @brief clear the simulation and delete all objects (empty grid)
     */
    void clear();

    /**
     * @brief Get the dimension of the simulation world
     * 
     * @return unsigned int
     */
    unsigned get_dimension();

    /**
     * @brief Default simulation constructor
     * 
     * @param engine pointer to the random engine
     */
    Simulation(std::default_random_engine* engine);

    /**
     * @brief Destroy the Simulation object
     * 
     * @note frees all the memory occupied by the simulation and its food & anthills
     */
    ~Simulation();
};

#endif
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

#include "anthill.h"
#include "nutrition.h"

/**
 * @class simulation
 * 
 * @brief Class that can create the base scenario of the map from a configfile
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
     * @brief Distribute one line of the configfile
     * 
     * @param line string of one line
     * 
     * @returns true if no error occured while reading the line
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
     * @brief Get the total food existing in the world
     * 
     * @return unsigned int
     */
    unsigned get_nbF();

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
     * @returns true if everything could be initialized
     */
    bool read_configfile(const std::string& filename);

    /**
     * @brief Store the actual state of the simulation in a configfile
     */
    void write_configfile();

    /**
     * @brief clear the simulation and delete all objects (empty grid)
     */
    void clear();

    /**
     * @brief Default simulation constructor
     */
    Simulation() : food() {};

    /**
     * @brief Destroy the Simulation object
     * 
     * @note frees all the memory occupied by the simulation and its food & anthills
     */
    ~Simulation();
};

#endif
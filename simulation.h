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
     * @brief Function to distribute one line of the configfile
     * 
     * @param line string of one line
     */
    void handle_line(const std::string& line);

public:
    /**
     * @brief Function to read the configfile
     */
    void read_configfile(const std::string& filename);

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
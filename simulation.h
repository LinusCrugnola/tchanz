/******************************************************************************!
* @file     simulation.h
* @author   Léo Brückl <leo.bruckl@epfll.ch>            
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
     * @brief Nutrition instances
     */
    std::vector<Nutrition*> nutrition;

    /**
     * @brief Function to distribute one line of the configfile
     * 
     * @param line string of one line
     */
    void handle_line(std::string line);

public:
    /**
     * @brief Function to read the configfile
     */
    void read_configfile(std::string filename);

    /**
     * @brief Default simulation constructor
     */
    Simulation(){}
};

#endif
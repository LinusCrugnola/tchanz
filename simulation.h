/******************************************************************************!
* @file     simulation.h
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

#include "anthill.h"
#include "nutrition.h"

class Simulation {
private:
    /**
     * @brief Anthill instances 
     */
    std::vector<Anthill> anthill;

    /**
     * @brief Nutrition instances
     */
    std::vector<Nutrition> nutrition;

    /**
     * @brief Function to decode one line of configfile
     */
    void decode_line(std::string line);

public:
    /**
     * @brief Function to read the configfile
     */
    void read_configfile(std::string filename);
};

#endif
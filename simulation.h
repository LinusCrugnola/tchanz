/****************************************************************!
  \file     simulation.h
  \author   Léo Brückl, Linus Crugnola
  \date     31.03.2022
  \brief    simulation interface
*****************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

#include "anthill.h"
#include "nutrition.h"

class Simulation {
private:
    // Anthill instances
    std::vector<Anthill> anthill;

    // Nutrition instances
    std::vector<Nutrition> nutrition;

    // function to decode one line of configfile
    void decode_line(std::string line);

public:
    // function to read the configfile
    void read_configfile(std::string filename);
};

#endif
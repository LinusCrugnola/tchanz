/****************************************************************!
  \file     simulation.h
  \author   Léo Brückl, Linus Crugnola
  \date     30.03.2022
  \brief    simulation interface
*****************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "squarecell.h"
#include "constantes.h"
#include "nutrition.h"
#include "anthill.h"

class Simulation
{
private:

    // Anthill instances
    std::vector<Anthill> anthill;

    // Nutrition instances
    std::vector<Nutrition> nutrition;
    
    // private functions:
    void decode_line(std::string line);
public:
    void read_configfile(std::string filename);
};




#endif
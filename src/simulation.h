/****************************************************************!
  \file     simulation.h
  \author   Léo Brückl, Linus Crugnola
  \date     22.03.2022
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

class Simulation
{
private:
    // Nutrition instances
    std::vector<Nutrition> nutrition;
    // Anthill instances
    //std::vector<Anthill> anthills; TODO: implement anthill

    // private functions:
    void decode_line(std::string line);
public:
    void read_configfile(std::string filename);
};




#endif
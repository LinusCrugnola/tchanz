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

class Simulation
{
private:
    void decode_line(std::string line);
public:
    Simulation(/* args */);
    ~Simulation();
    void read_configfile(std::string filename);
};

Simulation::Simulation(/* args */)
{

}

Simulation::~Simulation()
{
    
}


#endif
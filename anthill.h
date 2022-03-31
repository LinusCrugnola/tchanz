/****************************************************************!
 \file     anthill.h
 \author   Léo Brückl, Linus Crugnola
 \date     31.03.2022
 \brief    anthill interface
*****************************************************************/
 
#ifndef ANTHILL_H
#define ANTHILL_H
 
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "error_squarecell.h"
#include "squarecell.h"
#include "ants.h"

class Anthill
{
    private:
        square anthill_type;
        unsigned total_food;
        unsigned nbC, nbD, nbP;

        std::vector<Generator> generator;
        std::vector<Collector> collectors;
        std::vector<Defensor> defensors;
        std::vector<Predator> predators;
    
    public:
        square get_anthill_type() const
        {
            return anthill_type;
        }

        static Anthill anthill_validation(std::istringstream& data,
                                        std::vector<Anthill> anthills, unsigned home);
        unsigned anthill_get_ants(); 
        void ant_validation(std::istringstream& data, unsigned home);

        Anthill(square anthill_type, unsigned total_food, unsigned nbC, unsigned nbD,
                unsigned nbP, unsigned xg, unsigned yg, unsigned home)
                : anthill_type(anthill_type),
        total_food(total_food), nbC(nbC), nbD(nbD), nbP(nbP){
            this->generator.push_back(Generator::data_validation(xg, yg, anthill_type,
                                                                home));
        }


        







};





#endif
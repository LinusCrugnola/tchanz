/****************************************************************!
 \file     anthill.h
 \author   Léo Brückl, Linus Crugnola
 \date     30.03.2022
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

        //Ants:
        //FIXME: how can we have only one generator (error)
        //Generator generator;
        std::vector<Generator> generator;
        std::vector<Collector> collectors;
        std::vector<Defensor> defensors;
        std::vector<Predator> predators;
    
        //Formule de sizeF = partie_entière(sqrt(4*(sizeG*sizeG+sizeC*sizeC*nbC+sizeD*sizeD*nbD+sizeP*sizeP*nbP)))
        //(sizeF+2=side...?)
        //Constructeur sizeF à faire
    public:
        /*Anthill(int sizeF) : sizeF(sizeF)
        { 
            //sizeF formula
        }*/
        square get_anthill_type() const
        {
            return anthill_type;
        }


        static Anthill anthill_validation(std::istringstream& data,std::vector<Anthill> anthills, unsigned home);
        unsigned anthill_get_ants();
        void ant_validation(std::istringstream& data, unsigned home);

        Anthill(square anthill_type, unsigned total_food, unsigned nbC, unsigned nbD, unsigned nbP, unsigned xg, unsigned yg, unsigned home) : anthill_type(anthill_type), 
        total_food(total_food), nbC(nbC), nbD(nbD), nbP(nbP){
            this->generator.push_back(Generator::data_validation(xg, yg, anthill_type, home));
        }


        







};





#endif
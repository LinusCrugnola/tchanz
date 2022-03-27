#ifndef FOURMILIERE_H
 #define FOURMILIERE_H
 
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "error_squarecell.h"
#include "squarecell.h"

class Anthill
{
    private:
        unsigned x,y;
        unsigned side;
        //Formule de sizeF = partie_entière(sqrt(4*(sizeG*sizeG+sizeC*sizeC*nbC+sizeD*sizeD*nbD+sizeP*sizeP*nbP)))
        //(sizeF+2=side...?)
        //Constructeur sizeF à faire
        

    public:
        /*Anthill(int sizeF) : sizeF(sizeF)
        { 
            //sizeF formula
        }*/
        static Anthill data_validation(std::string line);
        Anthill(unsigned x,unsigned y, unsigned side) : x(x) , y(y) , side(side)
        {
            square_add({x,y,side,0});
        }
        







};





#endif
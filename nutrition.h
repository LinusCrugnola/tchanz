/****************************************************************!
 \file     nutrition.h
 \author   Léo Brückl, Linus Crugnola
 \date     30.03.2022
 \brief    nutrition interface
*****************************************************************/
#ifndef NUTRITION_H
#define NUTRITION_H
 
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "error_squarecell.h"
#include "squarecell.h"

class Nutrition
{
    private:
        unsigned x,y;
        double val_food;
    public:
        static Nutrition data_validation(std::istringstream& data);
        Nutrition(unsigned x_coor, unsigned y_coor) : x(x_coor) , y(y_coor)
        {
            square_add({x, y, 1, 1});
        }
};

#endif
 





 
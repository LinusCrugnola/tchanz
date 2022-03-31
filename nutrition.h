/******************************************************************************!
* @file     nutrition.h
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/
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
        //Verification if coordinates fit in the grid and if it has a distance bigger
        //than 1 from the border. Verifies if it overlaps with another entity.
        static Nutrition data_validation(std::istringstream& data);
        
        Nutrition(unsigned x_coor, unsigned y_coor) : x(x_coor) , y(y_coor)
        {
            square_add({x, y, 1, 1});
        }
};

#endif
 





 
/******************************************************************************!
* @file     nutrition.h
* @author   Léo Brückl <leo.bruckl@epfll.ch>            
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
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
        /**
         * @brief Verification if coordinates fit in the grid and if it has a distance
         * bigger than 1 from the border. 
         * Also verifies if it overlaps with another entity.
         */
        static Nutrition* data_validation(std::istringstream& data);

        /**
         * @brief Construct a new Nutrition object
         */        
        Nutrition(unsigned x_coor, unsigned y_coor) : x(x_coor) , y(y_coor)
        {
            square_add({x, y, 1, 1});
        }
        ~Nutrition(){square_delete({this->x, this->y, 1,0});}
};

#endif
 





 
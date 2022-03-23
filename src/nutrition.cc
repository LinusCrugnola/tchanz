/****************************************************************!
 \file     nutrition.cc
 \author   Léo Brückl, Linus Crugnola
 \date     22.03.2022
 \brief    nutrition implementation
*****************************************************************/

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "nutrition.h"
#include "message.h"
#include "squarecell.h"
#include "error_squarecell.h"

using namespace std;

bool Nutrition::data_validation(unsigned x_coor, unsigned y_coor){
    //convert line to stringstream
    //istringstream data(line);
    //read x, y
    //unsigned x_coor,y_coor;
    /*if(!(data >> x_coor >> y_coor))
    {
        return false;
    }*/

    if(square_validation({x_coor,y_coor,3,1}))
    {
        return false;
    }

    if(square_superposition({x_coor,y_coor,1,1}))
    {
        std::string food_overlap(x_coor,y_coor);
    }
}



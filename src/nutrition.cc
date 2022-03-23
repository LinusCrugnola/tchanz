/****************************************************************!
 \file     nutrition.cc
 \author   Léo Brückl, Linus Crugnola
 \date     22.03.2022
 \brief    nutrition implementation
*****************************************************************/

#include <vector>
#include <iostream>

#include "nutrition.h"
#include "message.h"
#include "squarecell.h"

using namespace std;

bool Nutrition::data_validation(std::string line){
    //convert line to stringstream
    //read x, y
    //validate x,y (squarecell)
    //chek superposition (squarecell)
}


void add_food(unsigned int x, unsigned int y)
{
    if(grid[x][g_max-1-y]) //Step to control if cell is empty
    {
        std::string food_overlap(x,y);
    }
    else
    {
        grid[x][g_max-1-y]=true;
    }
}



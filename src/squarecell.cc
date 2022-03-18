/****************************************************************!
  \file     squarecell.cc
  \author   Léo Brückl, Linus Crugnola
  \date     date
  \brief    squarecell implementation
*****************************************************************/

#include "squarecell.h"
//#include "error_squarecell.h"
#include <vector>
#include <iostream>

//functions
void Squarecell::square_validation(unsigned x, unsigned y, unsigned side, bool centered){
    // Check the point
    if(x<0 || x>(g_max-1)){
        //std::cout << error_squarecell::print_index(x, g_max-1);
        std::exit(EXIT_FAILURE);
    }
    else if(y<0 || y>(g_max-1)){
        // std::cout << error_squarecell::print_index(x, g_max-1);
        std::exit(EXIT_FAILURE);
    }
    // Check side
    if(centered){
        if(side%2 != 0){
            // std::cout << "Side is not an odd number";
            std::exit(EXIT_FAILURE);
        }
        else if((x+side/2)<0 || (x-side/2)>g_max-1){
            // std::cout << error_squarecell::print_outside(x, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
        else if((y+side/2)<0 || (y-side/2)>g_max-1){
            // std::cout << error_squarecell::print_outside(y, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
    }
    else{
        if((x+side)>g_max-1){
            // std::cout << error_squarecell::print_outside(x, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
        else if((y+side)>g_max-1){
            // std::cout << error_squarecell::print_outside(y, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
    }
}

bool Squarecell::square_superposition(unsigned x, unsigned y, unsigned side, bool centered){
    if(centered){
        for(unsigned i=y+side/2; i>y-side/2; i--){
            for(unsigned j=x-side/2; j<x+side/2; j++){
                if(!grid[j][i]){
                    return false;
                }
            }
        }
    }
    else{
        for(unsigned i=y; i>y-side; i--){
            for(unsigned j=x; j<x+side; j++){
                if(!grid[j][i]){
                    return false;
                }
            }
        }
    }
    return true;
}

//FIXME: Index problem
bool Squarecell::square_add(unsigned x, unsigned y, unsigned side, bool centered){
    if(centered){
        for(unsigned i=y+side/2; i>y-side/2; i--){
            for(unsigned j=x-side/2; j<x+side/2; j++){
                grid[j][i] = true;
            }
        }
    }
    else{
        for(unsigned i= g_max-1-y; i>g_max-1-y-side; i--){
            for(unsigned j=x; j<x+side; j++){
                grid[j][i] = true;
            }
        }
    }
    return true;
}

//TODO: check if there is a square to be deleted
bool Squarecell::square_delete(unsigned x, unsigned y, unsigned side, bool centered){
    return 0;
}

//print function:
void Squarecell::print_grid(){
    for(unsigned i=this->g_max; i>0; i--){
        std::cout << std::endl;
        for(unsigned j=0; j<this->g_max; j++){
            if(this->grid[j][i]){
                std::cout << "1 ";
            }
            else{
                std::cout << "0 ";
            }
        }
    }
}

unsigned Squarecell::get_gmax(){
    return this->g_max;
}
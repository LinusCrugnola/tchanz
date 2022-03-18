/****************************************************************!
  \file     squarecell.cc
  \author   Léo Brückl, Linus Crugnola
  \date     date
  \brief    squarecell implementation
*****************************************************************/

#include "squarecell.h"
#include "error_squarecell.h"
#include <vector>
#include <iostream>

//functions
void Squarecell::square_validation_test(unsigned x, unsigned y, unsigned side, bool centered){
    // Check the point
    if(x<0 || x>(g_max-1)){
        std::cout << error_squarecell::print_index(x, g_max-1);
        std::exit(EXIT_FAILURE);
    }
    else if(y<0 || y>(g_max-1)){
        std::cout << error_squarecell::print_index(y, g_max-1);
        std::exit(EXIT_FAILURE);
    }
    // Check side
    if(centered){
        if(side%2 == 0){
            std::cout << "Side is not an odd number";
            std::exit(EXIT_FAILURE);
        }
        else if((x-side/2)<0 || (x+side/2)>g_max-1){
            std::cout << error_squarecell::print_outside(x, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
        else if((y-side/2)<0 || (y+side/2)>g_max-1){
            std::cout << error_squarecell::print_outside(y, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
    }
    else{
        if((x+side)>g_max-1){
            std::cout << error_squarecell::print_outside(x, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
        else if((y+side)>g_max-1){
            std::cout << error_squarecell::print_outside(y, side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
    }
}

bool Squarecell::square_superposition_test(unsigned x, unsigned y, unsigned side, bool centered){
    if(centered){
        for(unsigned i=y-side/2; i<=y+side/2; i++){
            for(unsigned j=x-side/2; j<=x+side/2; j++){
                if(this->grid[j][this->g_max-1-i]){
                    return false;
                }
            }
        }
    }
    else{
        for(unsigned i=y; i<y+side; i++){
            for(unsigned j=x; j<x+side; j++){
                if(this->grid[j][this->g_max-1-i]){
                    return false;
                }
            }
        }
    }
    return true;
}

bool Squarecell::square_add(unsigned x, unsigned y, unsigned side, bool centered){
    if(centered){
        for(unsigned i=y-side/2; i<=y+side/2; i++){
            for(unsigned j=x-side/2; j<=x+side/2; j++){
                this->grid[j][this->g_max-1-i] = true;
            }
        }
    }
    else{
        for(unsigned i=y; i<y+side; i++){
            for(unsigned j=x; j<x+side; j++){
                this->grid[j][this->g_max-1-i] = true;
            }
        }
    }
    return true;
}

void Squarecell::set_coordinate(unsigned x, unsigned y){
    this->grid[x][g_max-1-y] = true;
}

//TODO: check if there is a square to be deleted
bool Squarecell::square_delete(unsigned x, unsigned y, unsigned side, bool centered){
    return 0;
}

//print function:
void Squarecell::print_grid(){
    for(unsigned i=0; i<this->g_max; i++){
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
    std::cout << std::endl << "_____________" << std::endl;
}

unsigned Squarecell::get_gmax(){
    return this->g_max;
}
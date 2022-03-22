/****************************************************************!
  \file     squarecell.cc
  \author   Léo Brückl, Linus Crugnola
  \date     22.03.2022
  \brief    squarecell implementation
*****************************************************************/

#include "squarecell.h"
#include "error_squarecell.h"
#include <vector>
#include <iostream>

namespace{
	unsigned g_max = 16;
    std::vector<std::vector<bool>> grid(g_max, std::vector<bool>(g_max, false));
}

//functions
void square_validation_test(square square){
    // Check the point
    if(square.x<0 || square.x>(g_max-1)){
        std::cout << error_squarecell::print_index(square.x, g_max-1);
        std::exit(EXIT_FAILURE);
    }
    else if(square.y<0 || square.y>(g_max-1)){
        std::cout << error_squarecell::print_index(square.y, g_max-1);
        std::exit(EXIT_FAILURE);
    }
    // Check side
    if(square.centered){
        if(square.side%2 == 0){
            std::cout << "Side is not an odd number";
            std::exit(EXIT_FAILURE);
        }
        else if((square.x-square.side/2)<0 || (square.x+square.side/2)>g_max-1){
            std::cout << error_squarecell::print_outside(square.x, square.side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
        else if((square.y-square.side/2)<0 || (square.y+square.side/2)>g_max-1){
            std::cout << error_squarecell::print_outside(square.y, square.side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
    }
    else{
        if((square.x+square.side)>g_max-1){
            std::cout << error_squarecell::print_outside(square.x, square.side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
        else if((square.y+square.side)>g_max-1){
            std::cout << error_squarecell::print_outside(square.y, square.side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
    }
}

bool square_superposition_test(square square){
    if(square.centered){
        for(unsigned i=square.y-square.side/2; i<=square.y+square.side/2; i++){
            for(unsigned j=square.x-square.side/2; j<=square.x+square.side/2; j++){
                if(grid[j][g_max-1-i]){
                    return false;
                }
            }
        }
    }
    else{
        for(unsigned i=square.y; i<square.y+square.side; i++){
            for(unsigned j=square.x; j<square.x+square.side; j++){
                if(grid[j][g_max-1-i]){
                    return false;
                }
            }
        }
    }
    return true;
}

bool square_superposition_test(square square1, square square2){
    
};

bool square_add(square square){
    if(square.centered){
        for(unsigned i=square.y-square.side/2; i<=square.y+square.side/2; i++){
            for(unsigned j=square.x-square.side/2; j<=square.x+square.side/2; j++){
                grid[j][g_max-1-i] = true;
            }
        }
    }
    else{
        for(unsigned i=square.y; i<square.y+square.side; i++){
            for(unsigned j=square.x; j<square.x+square.side; j++){
                grid[j][g_max-1-i] = true;
            }
        }
    }
    return true;
}

void set_coordinate(unsigned x, unsigned y){
    grid[x][g_max-1-y] = true;
}

//TODO: check if there is a square to be deleted
bool square_delete(square square){
    return 0;
}

//print function:
void print_grid(){
    for(unsigned i=0; i<g_max; i++){
        std::cout << std::endl;
        for(unsigned j=0; j<g_max; j++){
            if(grid[j][i]){
                std::cout << "1 ";
            }
            else{
                std::cout << "0 ";
            }
        }
    }
    std::cout << std::endl << "_____________" << std::endl;
}
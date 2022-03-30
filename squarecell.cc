/****************************************************************!
  \file     squarecell.cc
  \author   Léo Brückl, Linus Crugnola
  \date     30.03.2022
  \brief    squarecell implementation
*****************************************************************/

#include "squarecell.h"
#include "error_squarecell.h"
#include <vector>
#include <iostream>


// definition of grid
namespace{
    std::vector<std::vector<bool>> grid(g_max, std::vector<bool>(g_max, false));
}

//functions
bool square_validation(square square){
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
        if((square.x+square.side-1)>g_max-1){
            std::cout << error_squarecell::print_outside(square.x, square.side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
        else if((square.y+square.side-1)>g_max-1){
            std::cout << error_squarecell::print_outside(square.y, square.side, g_max-1);
            std::exit(EXIT_FAILURE);
        }
    }
    return true;
}

bool square_superposition(square square){
    if(square.centered){
        for(unsigned i=square.y-square.side/2; i<=square.y+square.side/2; i++){
            for(unsigned j=square.x-square.side/2; j<=square.x+square.side/2; j++){
                if(grid[j][g_max-1-i]){
                    return true;
                }
            }
        }
    }
    else{
        for(unsigned i=square.y; i<square.y+square.side; i++){
            for(unsigned j=square.x; j<square.x+square.side; j++){
                if(grid[j][g_max-1-i]){
                    return true;
                }
            }
        }
    }
    return false;
}

square square_get_superposition(square test){
    square cross;
    if(test.centered){
        for(unsigned i=test.y+test.side/2; i>=test.y-test.side/2; i--){
            for(unsigned j=test.x-test.side/2; j<=test.x+test.side/2; j++){
                if(grid[j][g_max-1-i]){
                    cross = {j,i,1,1};
                    return cross;
                }
            }
        }
    }
    else{
        for(unsigned i=test.y+test.side-1; i>=test.y; i--){
            for(unsigned j=test.x; j<test.x+test.side; j++){
                if(grid[j][g_max-1-i]){
                    cross = {j,i,1,1};
                    return cross;
                }
            }
        }
    }
    //default return
    return {500,500,0,0};
}

bool square_superposition(square s1, square s2){
    // check x
    int xmin, x1min, x2min;
    x1min = s1.centered ? s1.x-s1.side/2 : s1.x;
    x2min = s2.centered ? s2.x-s2.side/2 : s2.x;    
    int xmax;
    if(x1min < x2min){
        xmin = x2min;
        xmax = s1.centered ? s1.x+s1.side/2 : s1.x+s1.side-1;
    }
    else{
        xmin = x1min;
        xmax = s2.centered ? s2.x+s2.side/2 : s2.x+s2.side-1;
    }
    if(xmax >= xmin){
        //check y
        int ymin, y1min, y2min;
        y1min = s1.centered ? s1.y-s1.side/2 : s1.y;
        y2min = s2.centered ? s2.y-s2.side/2 : s2.y;    
        int ymax;
        if(y1min < y2min){
            ymin = y2min;
            ymax = s1.centered ? s1.y+s1.side/2 : s1.y+s1.side-1;
        }
        else{
            ymin = y1min;
            ymax = s2.centered ? s2.y+s2.side/2 : s2.y+s2.side-1;
        }
        if(ymax >= ymin){
            return true;
        }
    }
    return false;
}

// function to check if s2 is contained in s1 (not on border) s2 centered, s1 not
bool square_contains(square s1, square s2){
    if(s2.x-s2.side/2 <= s1.x) return false;
    else if(s2.x+s2.side/2 >= s1.x+s1.side-1) return false;
    else if(s2.y-s2.side/2 <= s1.y) return false;
    else if(s2.y+s2.side/2 >= s1.y+s1.side-1) return false;
    return true;
}

bool square_add(square square){
    if(!square_validation(square)) return false;
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

bool square_delete(square square){
    if(!square_validation(square)) return false;
    if(square.centered){
        for(unsigned i=square.y-square.side/2; i<=square.y+square.side/2; i++){
            for(unsigned j=square.x-square.side/2; j<=square.x+square.side/2; j++){
                if(!grid[j][g_max-1-i]) return false;
            }
        }
        for(unsigned i=square.y-square.side/2; i<=square.y+square.side/2; i++){
            for(unsigned j=square.x-square.side/2; j<=square.x+square.side/2; j++){
                grid[j][g_max-1-i] = false;
            }
        }
    }
    else{
        for(unsigned i=square.y; i<square.y+square.side; i++){
            for(unsigned j=square.x; j<square.x+square.side; j++){
                if(!grid[j][g_max-1-i]) return false;
            }
        }
        for(unsigned i=square.y; i<square.y+square.side; i++){
            for(unsigned j=square.x; j<square.x+square.side; j++){
                grid[j][g_max-1-i] = false;
            }
        }
    }
    return true;
}

//print function (Debug):
void print_grid(){
    for(unsigned i=0; i<g_max; i++){
        std::cout << std::endl;
        for(unsigned j=0; j<g_max; j++){
            if(grid[j][i]){
                std::cout << "\033[41;1mX\033[0m";
            }
            else{
                std::cout << "\033[42;1mX\033[0m";
            }
        }
    }
    std::cout << std::endl << "_____________" << std::endl;
}
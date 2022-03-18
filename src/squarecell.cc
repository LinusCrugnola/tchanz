//#include "squarecell.h"
//#include "error_squarecell.h"
#include <vector>
#include <iostream>

//Variables known to the whole module
namespace{
    unsigned g_max = 16;
    std::vector<std::vector<bool>> grid(g_max,std::vector<bool>(g_max, false));
}

//functions
void square_validation(unsigned x, unsigned y, unsigned side, bool centered){
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

bool square_superposition(unsigned x, unsigned y, unsigned side, bool centered){
    if(centered){
        for(int i=y+side/2; i>y-side/2; i--){
            for(int j=x-side/2; j<x+side/2; j++){
                if(!grid[j][i]){
                    return false;
                }
            }
        }
    }
    else{
        for(int i=y; i>y-side; i--){
            for(int j=x; j<x+side; j++){
                if(!grid[j][i]){
                    return false;
                }
            }
        }
    }
    return true;
}

//Index problem
bool square_block(unsigned x, unsigned y, unsigned side, bool centered){
    if(centered){
        for(int i=y+side/2; i>y-side/2; i--){
            for(int j=x-side/2; j<x+side/2; j++){
                grid[j][i] = true;
            }
        }
    }
    else{
        for(int i= g_max-1-y; i>g_max-1-y-side; i--){
            for(int j=x; j<x+side; j++){
                grid[j][i] = true;
            }
        }
    }
    return true;
}

bool square_free(unsigned x, unsigned y, unsigned side, bool centered){
    return 0;
}

//print function:
void print_grid(std::vector<std::vector<bool>> grid){
    for(int i=g_max; i>0; i--){
        std::cout << std::endl;
        for(int j=0; j<g_max; j++){
            if(grid[j][i]){
                std::cout << "1  ";
            }
            else{
                std::cout << "0  ";
            }
        }
    }
}

int main(){
    bool lol = square_block(5,5,3,0);
    print_grid(grid);
}
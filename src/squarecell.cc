#include "squarecell.h"
#include "error_squarecell.h"
#include <vector>



void Squarecell::test_validation_centered_square(unsigned x, unsigned y, unsigned side, bool centered)
{
    //Will check if coordinate(spawn) is in the grid
    if(x>(g_max-1))
    {
        error_squarecell::print_index(x, g_max-1);
    }

    if(x>(g_max-1))
    {
        error_squarecell::print_index(y, g_max-1);
    }
    //Will check if square is in the grid
    if(side%2)
    {
        if(centered){
            if(((g_max-1)<x+side/2) or ((g_max-1)<y+side/2))
            {
                //Center spawned square is outside the border-> error
                error_squarecell::print_outside(x,side,g_max-1);
            }
        }
    }
}
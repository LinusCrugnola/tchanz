#include "squarecell.h"
#include "error_squarecell.h"



void Squarecell::test_validation_square(unsigned x, unsigned y, unsigned side, bool centered=true) const
{
    //Will check if coordinate(spawn) is in the grid
    bool test(false);
    unsigned int index;
    if((g_max-1)<x)
    {
        test=true;
        index=x;
    }

    if((g_max-1)<y)
    {
        test=true;
        index=y;
    }

    if(test)
    {
        cout << error_squarecell::print_index(index,g_max-1);
    }
    //Will check if square is in the grid
    if(side%2)
    {
        if(centered){
            if(((g_max-1)<x+side/2) or ((g_max-1)<y+side/2))
            {
                //Square is outside the border

            }

        }
        else{

        }

    }


}
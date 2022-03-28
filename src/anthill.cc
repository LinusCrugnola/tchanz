#include "anthill.h"
#include "message.h"


using namespace std;

Anthill Anthill::data_validation(string line)
{
    unsigned x_coor,y_coor;
    unsigned side;
    unsigned x_g, y_g;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    istringstream data(line);
    if(!(data >> x_coor >> y_coor >> side >> x_g >> y_g >> total_food >> nbC >> nbD >> nbP));
    square_validation({x_coor,y_coor,side,0});
    if(square_superposition({x_coor,y_coor,side,0}))
    {
        cout << message::homes_overlap(x_coor,y_coor) << endl;
        exit(EXIT_FAILURE);
    }
    Anthill anthill(x_coor,y_coor,side);
    
    
    return anthill;
}

int anthill_get_ants(unsigned nbC, unsigned nbD, unsigned nbP)
{
    unsigned nbT = 1 + nbC + nbD + nbP;
    return nbT;
    //not sure about this...
}
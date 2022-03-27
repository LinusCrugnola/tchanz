#include "anthill.h"
#include "message.h"


using namespace std;

Anthill Anthill::data_validation(string line)
{
    unsigned x_coor,y_coor;
    unsigned sizeF; //must verify sizeF
    istringstream data(line);
    if(!(data >> x_coor >> y_coor));
    square_validation({x_coor,y_coor,sizeF,0});
    if(square_position({x_coor,y_coor,sizeF,0}))
    {
        cout << message::homes_overlap(x_coor,y_coor) << endl;
        exit(EXIT_FAILURE);
    }
    Anthill anthill(x_coor,y_coor,sizeF);
    return anthill;

    
    
}
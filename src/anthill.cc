#include "anthill.h"
#include "message.h"


using namespace std;

Anthill Anthill::data_validation(string line)
{
    square anthill = {0,0,0,0};
    unsigned x_g, y_g;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    istringstream data(line);
    if(!(data >> anthill.x >> anthill.y >> anthill.side >> x_g >> y_g >> total_food >> nbC >> nbD >> nbP));
    square_validation(anthill);
    if(square_superposition(anthill))
    {
        cout << message::homes_overlap(anthill.x,anthill.y) << endl;
        exit(EXIT_FAILURE);
    }
    Anthill anthill_ (anthill, total_food, nbC, nbD, nbP);
    
    return anthill_;
}

unsigned Anthill::anthill_get_ants(const Anthill& anthill)
{
    return this->nbC + this->nbD + this->nbP + 1;
}
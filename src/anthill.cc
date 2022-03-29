#include "anthill.h"
#include "message.h"
#include "squarecell.h"


using namespace std;

Anthill Anthill::anthill_validation(istringstream& data,vector<Anthill> anthills)
{
    square anthill = {0,0,0,0};
    unsigned x_g, y_g;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    if(!(data >> anthill.x >> anthill.y >> anthill.side >> x_g >> y_g >> total_food >> nbC >> nbD >> nbP));
    if(anthills.size()==0)
    {
        if(square_validation(anthill))
        {
            Anthill anthill_(anthill, nbC, nbD, nbP, total_food);
            return anthill_;
        }
    }
    else
    {
        for(unsigned i(0);i<anthills.size();i++)
        {
            if(square_superposition(anthills[i].get_anthill_type(),anthill))
            {
                std::cout << message::homes_overlap(i+1, anthills.size()+1) << std::endl;
                exit(EXIT_FAILURE);
            }
            if(square_validation(anthill))
            {
                Anthill anthill_(anthill, nbC, nbD, nbP, total_food);
                return anthill_;
            }
        }
    }
}

/*bool Anthill::anthill_position_control(const vector<Anthill>& anthills)
{
    bool permission_pos=true;
    if(anthills.size()=1)
    {
        permission_pos=true;
    }
    else
    {
        for(unsigned i(0);i<=anthills.size()-2;i++)
        {
            square_superposition(anthills[i].anthill_type, anthills[anthills.size()].anthill_type);
        }
    }
}*/



unsigned Anthill::anthill_get_ants()
{
    return this->nbC + this->nbD + this->nbP + 1;
}
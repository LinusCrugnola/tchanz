#include "anthill.h"
#include "message.h"
#include "squarecell.h"
#include "ants.h"


using namespace std;

Anthill Anthill::anthill_validation(istringstream& data,vector<Anthill> anthills, unsigned home)
{
    square anthill = {0,0,0,0};
    unsigned xg, yg;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    if(!(data >> anthill.x >> anthill.y >> anthill.side >> xg >> yg >> total_food >> nbC >> nbD >> nbP)) cout << "reading error!" << endl;
    if(anthills.size()==0)
    {
        if(square_validation(anthill))
        {
            Anthill anthill_(anthill, total_food, nbC, nbD, nbP, xg, yg, home);
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
                Anthill anthill_(anthill, total_food, nbC, nbD, nbP, xg, yg, home);
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

void Anthill::ant_validation(istringstream& data, unsigned home){
    enum Ant_states {collector, defensor, predator, finale};
    static unsigned i = 0, total = this->nbC;
    static Ant_states state = collector;

    switch (state){
        case collector:
            if(i >= total){
                state = defensor;
                i = 0;
                total = this->nbD;
                break;
            }
            this->collectors.push_back(Collector::data_validation(data));
            break;
        case defensor:
            if(i >= total){
                state = predator;
                i = 0;
                total = this->nbP;
                break;
            }
            this->defensors.push_back(Defensor::data_validation(data, this->anthill_type, home));
            break;    
        case predator:
            if(i >= total){
                state = finale;
                break;
            }
            this->predators.push_back(Predator::data_validation(data));
            break;
        case finale:
            break;
    }
}
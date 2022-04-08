/******************************************************************************!
* @file     anthill.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             90 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     10 %
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include "anthill.h"

#include <iostream>

#include "message.h"

using namespace std;

Anthill::Anthill(csquare position, cunsigned total_food, cunsigned nbC, cunsigned nbD,
                cunsigned nbP, cunsigned xg, cunsigned yg, cunsigned home)
                : position(position), total_food(total_food), nbC(nbC), 
                nbD(nbD), nbP(nbP)
{
    Ant* new_generator = Generator::data_validation(xg, yg, position, home);
    if(new_generator != nullptr) this->ants.push_back(new_generator);
}

Anthill* Anthill::anthill_validation(istringstream& data,
                                     vector<Anthill*>& hills_existing, cunsigned home) {
    Anthill* anthill = nullptr;
    square position = {0, 0, 0, 0};
    unsigned xg, yg;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    if (!(data >> position.x >> position.y >> position.side >> xg >> yg >> 
          total_food >> nbC >> nbD >> nbP)) cout << "reading error!" << endl;

    if(!square_validation(position)) return nullptr;

    for (unsigned i(0); i < hills_existing.size(); i++) {
        if (square_superposition(hills_existing[i]->get_position(), position)) {
            std::cout << message::homes_overlap(i, hills_existing.size());
            return nullptr;
        }
    }

    anthill = new Anthill(position, total_food, nbC, nbD, nbP, xg, yg, home);
    return anthill;
}

unsigned Anthill::anthill_get_ants() const {
    return this->nbC + this->nbD + this->nbP + 1;
}

void Anthill::ant_validation(istringstream& data, cunsigned home) {
    enum Ant_states { collector, defensor, predator, finale };
    static unsigned i=0, total = this->nbC;
    static Ant_states state = collector;
    if (this->nbC == 0) {
        state = this->nbD == 0 ? predator : defensor;
    }
    Ant* new_ant = nullptr;

    switch (state) {
        case collector:
            new_ant = Collector::data_validation(data);
            if(new_ant != nullptr) this->ants.push_back(new_ant);
            i += 1;
            if (i >= total) {
                state = defensor;
                i = 0;
                total = this->nbD;
            }
            break;
        case defensor:
            new_ant = Defensor::data_validation(data, this->position,home);
            if(new_ant != nullptr) this->ants.push_back(new_ant);
            i += 1;
            if (i >= total) {
                state = predator;
                i = 0;
                total = this->nbP;
            }
            break;
        case predator:
            new_ant = Predator::data_validation(data);
            if(new_ant != nullptr) this->ants.push_back(new_ant);
            i += 1;
            if (i >= total) {
                state = finale;
            }
            break;
        case finale:
            break;
    }
}

Anthill::~Anthill(){
    // destroy all ants
    for(auto& ant : this->ants){
        delete ant;
        ant = nullptr;
    }
    square_delete(this->position);
}
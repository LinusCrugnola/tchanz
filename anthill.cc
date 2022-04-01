/******************************************************************************!
* @file     anthill.cc
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/

#include "anthill.h"
#include "ants.h"
#include "message.h"
#include "squarecell.h"

using namespace std;

//Anthill constructor
Anthill::Anthill(square position, unsigned total_food, unsigned nbC, unsigned nbD,
                unsigned nbP, unsigned xg, unsigned yg, unsigned home)
                : position(position), total_food(total_food), nbC(nbC), 
                nbD(nbD), nbP(nbP)
{
    this->ants.push_back(Generator::data_validation(xg, yg, position, home));
}

//Verification of an anthill's data. If it fits in the grid AND if it overlaps 
//with another anthill or entity
Anthill* Anthill::anthill_validation(istringstream& data,
                                     const vector<Anthill*>& hills_existing, const unsigned& home) {
    Anthill* anthill = nullptr;
    square position = {0, 0, 0, 0};
    unsigned xg, yg;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    if (!(data >> position.x >> position.y >> position.side >> xg >> yg >> 
          total_food >> nbC >> nbD >> nbP)) cout << "reading error!" << endl;

    square_validation(position); // throws error

    for (unsigned i(0); i < hills_existing.size(); i++) {
        if (square_superposition(hills_existing[i]->get_position(), position)) {
            std::cout << message::homes_overlap(i, hills_existing.size());
            exit(EXIT_FAILURE);
        }
    }

    anthill = new Anthill(position, total_food, nbC, nbD, nbP, xg, yg, home);
    return anthill;
}

//This function returns the number of ants in anthill
unsigned Anthill::anthill_get_ants() {
    return this->nbC + this->nbD + this->nbP + 1;
}

//Function which verifies if an ant fits in the grid. Then it is put in the respected 
//class list of an anthill
void Anthill::ant_validation(istringstream& data, unsigned home) {
    enum Ant_states { collector, defensor, predator, finale };
    static unsigned i=0, total = this->nbC;
    static Ant_states state = collector;
    if (this->nbC == 0) {
        state = this->nbD == 0 ? predator : defensor;
    }
    switch (state) {
        case collector:
            this->ants.push_back(Collector::data_validation(data));
            i += 1;
            if (i >= total) {
                state = defensor;
                i = 0;
                total = this->nbD;
            }
            break;
        case defensor:
            this->ants.push_back(Defensor::data_validation(data, this->position,home));
            i += 1;
            if (i >= total) {
                state = predator;
                i = 0;
                total = this->nbP;
            }
            break;
        case predator:
            this->ants.push_back(Predator::data_validation(data));
            i += 1;
            if (i >= total) {
                state = finale;
            }
            break;
        case finale:
            break;
    }
}
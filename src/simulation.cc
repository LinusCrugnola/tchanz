/****************************************************************!
  \file     simulation.cc
  \author   Léo Brückl, Linus Crugnola
  \date     22.03.2022
  \brief    simulation implementation
*****************************************************************/

#include <cassert>

#include "simulation.h"
#include "nutrition.h"

using namespace std;

void Simulation::read_configfile(std::string filename){
    ifstream file(filename);
    if(!file.fail()){
        string line;
        while(getline(file >> ws,line)){
            if(line[0] == '#') continue;
            Simulation::decode_line(line);
        }
    }
    else /*TODO: error could not open*/;
}

void Simulation::decode_line(string line){
    istringstream data(line);
    // States
    enum Reading_states {nbN, nourriture, nbF, anthill, collector, defensor, predator, finale};
    static unsigned state = nbN;
    // counter
    static unsigned i = 0, total = 0;
    // variable
    static unsigned j = 0, nbC, nbD, nbP;
    
    // lecture statemachine
    switch(state){
        case nbN:   // Initial state
            if(!(data >> total)) /*TODO: lecture format error*/;
            else i = 0;
            if(total == 0) state = nbF;
            else state = nourriture;
            break;
        case nourriture:
            // Validate data and create nutrition if valid
            this->nutrition.push_back(Nutrition::data_validation(line));
            i += 1;
            if(i >= total) state = nbF;
            break;
        case nbF:
            //to start:
            print_grid();
            exit(0);
            // if(!(data >> total)) /*TODO: lecture format error*/;
            // else i = 0;
            // if(total == 0) state = finale;
            // else state = heap;
            // break;
        case anthill:
            // int x, y, side, xg, yg, total_n;
            // if(!(data >> x >> y >> side >> xg >> yg >> total_n >> nbC >> nbD >> nbP)) /*TODO: lecture format error*/;
            // else{
            //     // TODO: fourmilière constructor
            // }
            //this->anthill.push_back(Anthill::anthill_validation(line));
            i += 1;
            state = collector;
            j = 0;
            break;
        case collector:
            if(j >= nbC){
                state = defensor;
                j = 0;
            }
            // int x, y, age, Etat_collector;
            // if(!(data >> x >> y >> age >> Etat_collector)) /*TODO: lecture format error*/;
            // else{
            //     // TODO: collector constructor
            // }
            j += 1;
            break;
        case defensor:
            if(j >= nbD){
                state = predator;
                j = 0;
            }
            // int x, y, age;
            // if(!(data >> x >> y >> age)) /*TODO: lecture format error*/;
            // else{
            //     // TODO: defensor constructor
            // }
            j += 1;
            break;
        case predator:
            // int x, y, age;
            // if(!(data >> x >> y >> age)) /*TODO: lecture format error*/;
            // else{
            //     // TODO: predator generator
            // }
            j += 1;
            if(j >= nbP){
                if(i >= total) state = finale;
                else state = anthill;
            }
            break;
        case finale:
            break;
    }
}
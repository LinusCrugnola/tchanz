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
    enum Reading_states {nbN, nourriture, nbF, anthill, ant, finale};
    static unsigned state = nbN;
    // counter
    static unsigned i = 0, total = 0;
    // variable
    static unsigned j = 0, total_ants;
    
    // lecture statemachine
    switch(state){
        case nbN:   // Initial state
            if(!(data >> total)) /*TODO: lecture format error*/;
            else i = 0;
            state = total == 0 ? nbF : nourriture;
            break;
        case nourriture:
            // Validate data and create nutrition if valid
            this->nutrition.push_back(Nutrition::data_validation(line));
            i += 1;
            if(i >= total) state = nbF;
            break;
        case nbF:
            if(!(data >> total)) /*TODO: lecture format error*/;
            else i = 0;
            state = total == 0 ? finale : anthill;
            break;
        case anthill:
            // Validate data and create anthill if valid
            this->anthill.push_back(Anthill::anthill_validation(data, this->anthill));
            //initialize ant counter
            total_ants = anthill[i-1].anthill_get_ants() - 1;
            j = 0;
            i += 1;
            state = ant;
            break;
        case ant:
            if(j >= total_ants){
                state = i >= total ? finale : anthill;
            }
            else j += 1;
            // create ant
            break;
        case finale:
            break;
    }
}
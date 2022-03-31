/****************************************************************!
  \file     simulation.cc
  \author   Léo Brückl, Linus Crugnola
  \date     30.03.2022
  \brief    simulation implementation
*****************************************************************/

#include <fstream>
#include <iostream>
#include <sstream>

#include "simulation.h"
#include "constantes.h"
#include "squarecell.h"

using namespace std;

void Simulation::read_configfile(std::string filename) {
    ifstream file(filename);
    if (!file.fail()) {
        string line;
        while (getline(file >> ws, line)) {
            if (line[0] == '#') continue;
            Simulation::decode_line(line);
        }
    }
    else
        cout << "error could not open file!" << endl;
}

void Simulation::decode_line(string line) {
    istringstream data(line);
    enum Reading_states {nbN, nourriture, nbF, anthill, ant, finale};
    static unsigned state = nbN;
    static unsigned i = 0, total = 0;
    static unsigned j = 0, total_ants;

    switch (state) {
        case nbN: 
            if (!(data >> total)) cout << "reading error!" << endl;   
            else i = 0;
            state = total == 0 ? nbF : nourriture;
            break;
        case nourriture:
            this->nutrition.push_back(Nutrition::data_validation(data));
            i += 1;
            if (i >= total) state = nbF;
            break;
        case nbF:
            if (!(data >> total)) cout << "reading error!" << endl;
            else i = 0;
            state = total == 0 ? finale : anthill;
            break;
        case anthill:
            this->anthill.push_back(Anthill::anthill_validation(data,this->anthill,i));
            total_ants = this->anthill[i].Anthill::anthill_get_ants()-1;
            j = 0;
            i += 1;
            if (total_ants == 0) state = i >= total ? finale : anthill;
            else state = ant;
            break;
        case ant:
            this->anthill[i-1].Anthill::ant_validation(data, i-1);
            j += 1;
            if (j >= total_ants) state = i >= total ? finale : anthill;
            break;
        case finale:
            break;
    }
}
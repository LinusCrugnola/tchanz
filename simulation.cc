/******************************************************************************!
* @file     simulation.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             40 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     60 %
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include "simulation.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "constantes.h"
#include "squarecell.h"

using namespace std;

void Simulation::read_configfile(const std::string& filename) {
    ifstream file(filename);
    if (!file.fail()) {
        string line;
        while (getline(file >> ws, line)) {
            if (line[0] == '#') continue;
            Simulation::handle_line(line);
        }
    }
    else
        cout << "error could not open file!" << endl;
}

void Simulation::handle_line(const string& line) {
    istringstream data(line);
    enum Reading_states {nbN, nutrition, nbF, anthill, ant, finale};
    static unsigned state = nbN;
    static unsigned i = 0, total = 0;
    static unsigned j = 0, total_ants;

    Anthill* new_hill = nullptr;

    switch (state) {
        case nbN: 
            if (!(data >> total)) cout << "reading error!" << endl;   
            else i = 0;
            state = total == 0 ? nbF : nutrition;
            break;
        case nutrition:
            this->food.add_element(data);
            i += 1;
            if (i >= total) state = nbF;
            break;
        case nbF:
            if (!(data >> total)) cout << "reading error!" << endl;
            else i = 0;
            state = total == 0 ? finale : anthill;
            break;
        case anthill:
            new_hill = Anthill::anthill_validation(data,this->anthill,i);
            if(new_hill != nullptr){
                this->anthill.push_back(new_hill);
                total_ants = this->anthill[i]->Anthill::anthill_get_ants()-1;
                j = 0;
                i += 1;
                if (total_ants == 0) state = i >= total ? finale : anthill;
                else state = ant;
            }
            state = i >= total ? finale : anthill;
            break;
        case ant:
            this->anthill[i-1]->Anthill::ant_validation(data, i-1);
            j += 1;
            if (j >= total_ants) state = i >= total ? finale : anthill;
            break;
        case finale:
            break;
    }
}

Simulation::~Simulation(){
    // free all the memory
    for(auto& hill : this->anthill){
        delete hill;
        hill = nullptr;
    }
    this->food.~Nutrition();
}
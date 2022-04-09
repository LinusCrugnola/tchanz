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
#include <ctime>

#include "constantes.h"
#include "squarecell.h"

void Simulation::read_configfile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.fail()) {
        std::string line;
        while (std::getline(file >> std::ws, line)) {
            if (line[0] == '#') continue;
            Simulation::handle_line(line);
        }
    }
    else
        std::cout << "error could not open file!" << std::endl;
}

void Simulation::handle_line(const std::string& line) {
    std::istringstream data(line);
    enum Reading_states {nbN, nutrition, nbF, anthill, ant, finale};
    static unsigned state = nbN;
    static unsigned i = 0, total = 0;
    static unsigned j = 0, total_ants;

    Anthill* new_hill = nullptr;

    switch (state) {
        case nbN: 
            if (!(data >> total)) std::cout << "reading error!" << std::endl;   
            else i = 0;
            state = total == 0 ? nbF : nutrition;
            break;
        case nutrition:
            this->food.add_element(data);
            i += 1;
            if (i >= total) state = nbF;
            break;
        case nbF:
            if (!(data >> total)) std::cout << "reading error!" << std::endl;
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
            //if invalid abort anthill
            else state = ++i >= total ? finale : anthill;
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

void Simulation::write_configfile(){
    std::ofstream file("./output.txt");
    if(!file.fail()){
        file << Simulation::get_fileheader();
        file << this->food.get_filedata();
        file << "\n" << std::to_string(this->anthill.size()) << " # nb anthill\n";
        for(unsigned i=0; i<this->anthill.size(); i++){
            if(i>0) file << "\n\n";
            file << this->anthill[i]->get_filedata(i+1);
        }
    }
    else std::cout << "problem writing file" << std::endl;
    file.close();
}

std::string Simulation::get_fileheader(){
    time_t now = time(0);
    tm *time = localtime(&now);

    return "# Saved scenario from: " + std::to_string(time->tm_mday) + "."
           + std::to_string(1 + time->tm_mon) + "." 
           + std::to_string(1900 + time->tm_year) + " at: " 
           + std::to_string(time->tm_hour) + ":" 
           + std::to_string(time->tm_min) + "\n";
}

Simulation::~Simulation(){
    // free all the memory
    for(auto& hill : this->anthill){
        delete hill;
        hill = nullptr;
    }
    this->food.~Nutrition();
}
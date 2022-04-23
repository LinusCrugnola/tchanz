/******************************************************************************!
* @file     simulation.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             30 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     70 %
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

bool Simulation::draw_current_state(){
    //call draw functions of entities
    if(!this->food.draw_all()) return false;
    for(const auto& hill : this->anthill){
        if(!hill->draw_all_children()) return false;
    }
    return true;
}

bool Simulation::read_configfile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.fail()) {
        std::string line;
        while (std::getline(file >> std::ws, line)) {
            if (line[0] == '#') continue;
            if(!Simulation::handle_line(line))
                return false;
        }
        return true;
    }
    else
        return false;
}

bool Simulation::handle_line(const std::string& line) {
    std::istringstream data(line);
    enum Reading_states {nbN, nutrition, nbF, anthill, ant, finale};
    static unsigned state = nbN;
    static unsigned i = 0, total = 0;
    static unsigned j = 0, total_ants;

    Anthill* new_hill = nullptr;

    switch (state) {
        case nbN: 
            if (!(data >> total)) return false;  
            else i = 0;
            state = total == 0 ? nbF : nutrition;
            break;
        case nutrition:
            if(!this->food.add_element(data)) return false;
            i += 1;
            if (i >= total) state = nbF;
            break;
        case nbF:
            if (!(data >> total)) return false;
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
                break;
            }
            return false;
        case ant:
            if(!this->anthill[i-1]->Anthill::ant_validation(data, i-1)) return false;
            j += 1;
            if (j >= total_ants) state = i >= total ? finale : anthill;
            break;
        case finale:
            break;
    }
    return true;
}

void Simulation::write_configfile(){
    // generate unique filename for output
    static unsigned file_count = 0;
    std::string filename = "./output";
    filename += file_count == 0 ? "" : std::to_string(file_count);
    filename += ".txt";

    //write file
    std::ofstream file(filename);
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
    file_count++;
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

void Simulation::clear(){
    this->food.clear();
    for(auto elem : this->anthill){
        delete elem;
        elem = nullptr;
    }
    this->anthill.clear();
}

Simulation::~Simulation(){
    // free all the memory
    for(auto& hill : this->anthill){
        delete hill;
        hill = nullptr;
    }
    //this->food.~Nutrition();
}
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

unsigned Simulation::get_nbF(){
    return this->food.get_nbF();
}

//unsigned Simulation::get_nbH

std::string Simulation::get_next_anthill_info(bool reverse){
    static int index = -1;
    unsigned anthill_size = this->anthill.size();
    if(anthill_size == 0){
        return "None selected";
    }
    else if(reverse){
        if(index == -1){
            index = anthill_size - 1;
            return "id: " + std::to_string(index) + "\n" + 
                    this->anthill[index]->get_info();
        }
        if(index == 0){
            index = -1;
            return "None selected";
        }
        index -= 1;
        return "id: " + std::to_string(index) + "\n" + 
                this->anthill[index]->get_info();
    }
    else{
        if(index+1 >= (int) anthill_size){
            index = -1;
            return "None selected";
        }
        index += 1;
        return "id: " + std::to_string(index) + "\n" + 
                this->anthill[index]->get_info();
    }
}

bool Simulation::draw_current_state(){
    //call draw functions of entities
    if(!this->food.draw_all()) return false;
    for(const auto& hill : this->anthill){
        if(!hill->draw_all_children()) return false;
    }
    return true;
}

bool Simulation::read_configfile(const std::string& filename) {
    this->clear();
    //reset colors
    scl::get_new_color(true);
    std::ifstream file(filename);
    if (!file.fail()) {
        std::string line;
        while (std::getline(file >> std::ws, line)) {
            if (line[0] == '#') continue;
            if(!Simulation::handle_line(line)){
                this->clear();
                return false;
            }
        }
        //realnce pour reset
        Simulation::handle_line("");
        return true;
    }
    else{
        this->clear();
        return false;
    }
}

bool Simulation::handle_line(const std::string& line) {
    std::istringstream data(line);
    enum Reading_states {nbF, nutrition, nbH, anthill, ant, finale};
    static unsigned state = nbF;
    static unsigned i = 0, total = 0;
    static unsigned j = 0, total_ants;

    bool success = true;

    Anthill* new_hill = nullptr;

    switch (state) {
        case nbF: 
            if (!(data >> total)) success = false;  
            else i = 0;
            state = total == 0 ? nbH : nutrition;
            break;
        case nutrition:
            if(!this->food.add_element(data)) success = false;
            i += 1;
            if (i >= total) state = nbH;
            break;
        case nbH:
            if (!(data >> total)) success = false;
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
            success = false;
        case ant:
            if(!this->anthill[i-1]->Anthill::ant_validation(data, i-1))
                success = false;
            j += 1;
            if (j >= total_ants){
                state = i >= total ? finale : anthill;
                //rerun for state finale
                this->anthill[i-1]->Anthill::ant_validation(data, i-1);
            }
            break;
        case finale:
            state = nbF;
            i = 0;
            j = 0;
            total = 0;
            total_ants = 0;
            break;
    }
    if(!success){
        state = nbF;
        i = 0;
        j = 0;
        total = 0;
        total_ants = 0;   
        return false;
    }
    return true;
}

void Simulation::write_configfile(const std::string& filename){
    // // generate unique filename for output
    // static unsigned file_count = 0;
    // std::string filename = "./output";
    // filename += file_count == 0 ? "" : std::to_string(file_count);
    // filename += ".txt";

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
    //file_count++;
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

unsigned Simulation::get_dimension(){
    return scl::g_max;
}

Simulation::~Simulation(){
    // free all the memory
    for(auto& hill : this->anthill){
        delete hill;
        hill = nullptr;
    }
    //this->food.~Nutrition();
}
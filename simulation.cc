/******************************************************************************!
* @file     simulation.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             20 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     80 %
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include "simulation.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <random>

#include "constantes.h"
#include "squarecell.h"
#include "message.h"

std::default_random_engine Simulation::rand_engine;

unsigned Simulation::get_nbF(){
    return this->food.get_nbF();
}

/**
 * @brief state messages
 */
const std::string st_read =  "\n----------------- File Lecture ---------------------";
const std::string st_clear = "\n----------------- Abort Lecture --------------------";
const std::string st_init =  "\n----------------- Initialize Simulation ------------";

std::string Simulation::get_next_anthill_info(bool reverse, bool reset){
    static int index = -1;
    static bool last_highlighted = false;
    if(reset){
        last_highlighted = false;
        this->clear_highlights();
        index = -1;
        return "None selected          \n";
    }
    if(last_highlighted){
        this->anthill[index]->delete_highlight();
        last_highlighted = false;
    }
    unsigned anthill_size = this->anthill.size();
    if(anthill_size == 0){
        return "None selected          \n";
    }
    else if(reverse){
        if(index == -1){
            index = anthill_size - 1;
            this->anthill[index]->set_highlight();
            last_highlighted = true;
            return "id: " + std::to_string(index) + "\n" + 
                    this->anthill[index]->get_info();
        }
        if(index == 0){
            index = -1;
            return "None selected          \n";
        }
    }
    else{
        if(index+1 >= (int) anthill_size){
            index = -1;
            return "None selected          \n";
        }
    }
    index = reverse ? index - 1 : index + 1;
    this->anthill[index]->set_highlight();
    last_highlighted = true;
    return "id: " + std::to_string(index) + "\n" + this->anthill[index]->get_info();
}

void Simulation::clear_highlights(){
    for(auto& hill : this->anthill){
        hill->delete_highlight();
    }
}

bool Simulation::update(){
    create_nutrition();
    for(auto& hill : this->anthill){
        hill->check_growth(anthill);
        hill->generator_action(&this->rand_engine, &this->food);
        if(!hill->is_dead()){
            hill->ants_action();
        }
    }
    for(auto& hill : this->anthill){
        if(hill->is_dead()){
            this->get_next_anthill_info(0,1);
            hill->~Anthill();
            hill = nullptr;
        }
        else hill->remove_dead_ants();
    }
    // erase all dead anthills
    this->anthill.erase(std::remove(this->anthill.begin(), this->anthill.end(), 
                                    nullptr), this->anthill.end());
    return true;
}

void Simulation::create_nutrition(){
    if(this->rand_bool(rand_engine)){
        for(unsigned i = 0; i < max_food_trial; i++){
            bool overlap = false;
            unsigned x = this->rand_int(rand_engine);
            unsigned y = this->rand_int(rand_engine);
            for(const auto& hill : this->anthill){
                if(scl::square_superposition(hill->get_position(), {x, y, 1, 1}))
                    overlap = true;
            }
            if(!overlap && this->food.add_element(x, y)){ //add only called if overlap
                break;
            }
        }
    }
}

bool Simulation::draw_current_state(){
    //call draw functions of entities
    if(!this->food.draw_all()) return false;
    for(const auto& hill : this->anthill){
        if(!hill->draw_hill()) return false;
    }
    for(const auto& hill : this->anthill){
        if(!hill->draw_ants());
    }
    return true;
}

bool Simulation::read_configfile(const std::string& filename) {
    this->clear();
    //reset colors
    scl::get_new_color(true);
    std::cout << st_read << std::endl;
    std::ifstream file(filename);
    if (!file.fail()) {
        std::string line;
        while (std::getline(file >> std::ws, line)) {
            if (line[0] == '#') continue;
            if(!Simulation::handle_line(line)){
                this->clear();
                std::cout << st_clear << std::endl;
                return false;
            }
        }
        //realnce pour reset
        Simulation::handle_line("");
        std::cout << message::success();
        std::cout << st_init << std::endl;
        return true;
    }
    else{
        this->clear();
        std::cout << st_clear << std::endl;
        return false;
    }
}

// First function longer than 40 lines
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
                total_ants = this->anthill[i]->Anthill::get_ants()-1;
                j = 0;
                i += 1;
                if (total_ants == 0) state = i >= total ? finale : anthill;
                else state = ant;
                break;
            }
            success = false;
            break;
        case ant:
            if(!this->anthill[i-1]->Anthill::ant_validation(data, i-1, &this->food)){
                success = false;
                break;
            }
            j += 1;
            if (j >= total_ants){
                state = i >= total ? finale : anthill;
                //rerun for state finale
                this->anthill[i-1]->Anthill::ant_validation(data, i-1, nullptr);
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
    for(auto elem : this->anthill){
        delete elem;
        elem = nullptr;
    }
    this->anthill.clear();
    this->food.clear();
}

unsigned Simulation::get_dimension(){
    return scl::g_max;
}

Simulation::Simulation() : food(), rand_bool(food_rate), rand_int(1, scl::g_max-2) {};

Simulation::~Simulation(){
    // free all the memory
    for(auto& hill : this->anthill){
        delete hill;
        hill = nullptr;
    }
}
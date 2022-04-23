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

Anthill::Anthill(scl::csquare position, cunsigned total_food, cunsigned nbC, 
                 cunsigned nbD,cunsigned nbP)
    : position(position), total_food(total_food), nbC(nbC), nbD(nbD), nbP(nbP)
{}

Anthill* Anthill::anthill_validation(std::istringstream& data,
                                     std::vector<Anthill*>& hills_existing, 
                                     cunsigned home) {
    Anthill* anthill = nullptr;
    scl::square position = {0, 0, 0, 0};
    unsigned xg, yg;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    if (!(data >> position.x >> position.y >> position.side >> xg >> yg >> total_food
               >> nbC >> nbD >> nbP)){
        std::cout << "reading error!" << std::endl;
    }

    if(!scl::square_validation(position)) return nullptr;

    for (unsigned i(0); i < hills_existing.size(); i++) {
        if (scl::square_superposition(hills_existing[i]->get_position(), position)) {
            std::cout << message::homes_overlap(i, hills_existing.size());
            return nullptr;
        }
    }

    anthill = new Anthill(position, total_food, nbC, nbD, nbP);

    Ant* new_generator = Generator::data_validation(xg, yg, position, home);
    if(new_generator != nullptr) anthill->ants.push_back(new_generator);
    else return nullptr;

    return anthill;
}

unsigned Anthill::anthill_get_ants() const {
    return this->nbC + this->nbD + this->nbP + 1;
}

bool Anthill::ant_validation(std::istringstream& data, cunsigned home) {
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
            else return false;
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
            else return false;
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
            else return false;
            i += 1;
            if (i >= total) {
                state = finale;
            }
            break;
        case finale:
            break;
    }
    return true;
}

std::string Anthill::get_filedata(unsigned home){
    std::string output = {};
    std::string gen_dat = this->ants[0]->get_filedata();
    // add anthill data
    output +=  "\t" +  std::to_string(this->position.x) 
              + " " +  std::to_string(this->position.y) 
              + " " +  std::to_string(this->position.side) + " " + gen_dat
              + " " +  std::to_string(this->total_food) 
              + " " +  std::to_string(this->nbC) + " " +  std::to_string(this->nbD)
              + " " +  std::to_string(this->nbP);
    output += " # anthill #" +  std::to_string(home) + "\n";
    // add ant data
    for(unsigned i=1; i<=nbC; i++){
        if(i == 1) output += "\n\t# collectors:\n";
        output += this->ants[i]->get_filedata();
    }
    for(unsigned i=nbC+1; i<=nbD+nbC; i++){
        if(i == nbC+1) output += "\n\t# defensors:\n";
        output += this->ants[i]->get_filedata();
    }
    for(unsigned i=nbD+nbC+1; i<=this->anthill_get_ants()-1; i++){
        if(i == nbD+nbC+1) output += "\n\t# predators:\n";
        output += this->ants[i]->get_filedata();
    }
    return output;
}

Anthill::~Anthill(){
    // destroy all ants
    for(auto& ant : this->ants){
        delete ant;
        ant = nullptr;
    }
    this->ants.clear();
    scl::square_delete(this->position);
}
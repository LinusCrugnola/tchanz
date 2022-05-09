/******************************************************************************!
* @file     anthill.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             90 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     10 %
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include "anthill.h"

#include <iostream>
#include <math.h>

#include "message.h"

Anthill::Anthill(scl::csquare position, cunsigned total_food, cunsigned nbC, 
                 cunsigned nbD, cunsigned nbP)
    : position(position), total_food(total_food), nbC(nbC), nbD(nbD), nbP(nbP), 
      anthill_state(FREE), end_of_klan(false), highlight(false) {
    this->color = scl::get_new_color();
}

bool Anthill::draw_hill() {
    return scl::square_draw(this->position, scl::empty, this->color, this->highlight);
}

bool Anthill::draw_ants() {
    for (const auto& ant : this->ants) {
        if (!ant->draw(this->color)) return false;
    }
    return true;
}

Anthill* Anthill::anthill_validation(std::istringstream& data,
                                     std::vector<Anthill*>& hills_existing, 
                                     cunsigned home) {
    Anthill* anthill = nullptr;
    scl::square position = {0, 0, 0, 0};
    unsigned xg, yg;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    if (!(data >> position.x >> position.y >> position.side >> xg >> yg >> total_food
               >> nbC >> nbD >> nbP)) {
        std::cout << "reading error!" << std::endl;
    }

    if (!scl::square_validation(position)) return nullptr;

    for (unsigned i(0); i < hills_existing.size(); i++) {
        if (scl::square_superposition(hills_existing[i]->get_position(), position)) {
            std::cout << message::homes_overlap(i, hills_existing.size());
            return nullptr;
        }
    }

    anthill = new Anthill(position, total_food, nbC, nbD, nbP);

    Ant* new_generator = Generator::data_validation(xg, yg, position, home);
    if (new_generator != nullptr)
        anthill->ants.push_back(new_generator);
    else
        return nullptr;

    return anthill;
}

unsigned Anthill::anthill_get_ants() const {
    return this->nbC + this->nbD + this->nbP + 1;
}

bool Anthill::generator_action() const {
    this->ants[0]->action(this->position);
    return true; 
}

bool Anthill::ants_action() const{
    for(unsigned i = 0; i < this->ants.size(); i++){
        this->ants[i]->action(this->position);
    }
    return true;
}

bool Anthill::ant_validation(std::istringstream& data, cunsigned home, 
                             Nutrition* nutrition) {
    enum Ant_states { collector, defensor, predator, finale };
    static unsigned i = 0, total = 0;
    static Ant_states state = collector;
    if (state == collector && total == 0) {
        total = this->nbC;
    }
    if (this->nbC == 0 && state == collector) {
        state = this->nbD == 0 ? predator : defensor;
        total = this->nbD == 0 ? this->nbP : this->nbD;
    }
    Ant* new_ant = nullptr;

    bool success = true;

    switch (state) {
        case collector:
            new_ant = Collector::data_validation(data, nutrition);
            if (new_ant != nullptr) this->ants.push_back(new_ant);
            else success = false;
            i += 1;
            if (i >= total) {
                state = defensor;
                i = 0;
                total = this->nbD;
            }
            break;
        case defensor:
            new_ant = Defensor::data_validation(data, this->position,home);
            if (new_ant != nullptr) this->ants.push_back(new_ant);
            else success = false;
            i += 1;
            if (i >= total) {
                state = predator;
                i = 0;
                total = this->nbP;
            }
            break;
        case predator:
            new_ant = Predator::data_validation(data);
            if (new_ant != nullptr) this->ants.push_back(new_ant);
            else success = false;
            i += 1;
            if (i >= total) {
                state = finale;
            }
            break;
        case finale:
            state = collector;
            total = 0;
            i = 0;
            break;
    }
    if (!success) {
        state = collector;
        total = 0;
        i = 0;
        return false;
    }
    return true;
}

void Anthill::set_highlight() {
    this->highlight = true;
}

void Anthill::delete_highlight() {
    this->highlight = false;
}

std::string Anthill::get_filedata(unsigned home) {
    std::string output = {};
    std::string gen_dat = this->ants[0]->get_filedata();
    // add anthill data
    output +=  "\t" +  std::to_string(this->position.x) 
              + " " +  std::to_string(this->position.y) 
              + " " +  std::to_string(this->position.side) + " " + gen_dat
              + " " +  std::to_string((int) this->total_food) 
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

std::string Anthill::get_info(){
    unsigned decimal_part = this->total_food*100 - int(this->total_food)*100;
    return "Total Food: " + std::to_string(int(this->total_food)) + "." +
           (decimal_part == 0 ? "00" : std::to_string(decimal_part)) + "\n\n" +
           "nbC: " + std::to_string(this->nbC) + "\n" +
           "nbD: " + std::to_string(this->nbD) + "\n" +
           "nbP: " + std::to_string(this->nbP) + 
           "                            \n";
}

bool Anthill::check_growth(std::vector<Anthill*>& hills){
    if(this->anthill_state == CONSTRAINED) return false;
    int new_size = sqrt(4 * (pow(sizeG, 2) + pow(sizeC, 2)*this->nbC 
                          + pow(sizeD, 2)*this->nbD + pow(sizeP, 2)*this->nbP));
    //check top right corner expansion
    scl::square new_position = this->position;
    //new_size = new_position.side - 1; //grow one field
    new_position.side = new_size + 2;
    if(this->update_position(new_position, hills)) return true;
    //check botton right corner expansion
    new_position = this->position;
    new_position.side = new_size + 2;
    new_position.y -= new_position.side - position.side;
    if(this->update_position(new_position, hills)) return true;
    //check botton left corner expansion
    new_position = this->position;
    new_position.side = new_size + 2;
    new_position.x -= new_position.side - position.side;
    new_position.y -= new_position.side - position.side;
    if(this->update_position(new_position, hills)) return true;
    //check top left corner expansion
    new_position = this->position;
    new_position.side = new_size + 2;
    new_position.x -= new_position.side - position.side;
    if(this->update_position(new_position, hills)) return true;
    this->anthill_state = CONSTRAINED;
    return false;
}

bool Anthill::update_position(scl::csquare new_position, std::vector<Anthill*>& hills){
    if(!scl::square_validation(new_position, scl::NOERR)) return false;
    unsigned superpos_count = 0;
    for(const auto& hill : hills){
        if(scl::square_superposition(new_position, hill->get_position()))
            superpos_count++;
    }
    if(superpos_count < 2){
        this->position = new_position;
        return true;
    }
    return false;
}

Anthill::~Anthill() {
    // destroy all ants
    for (auto& ant : this->ants) {
        delete ant;
        ant = nullptr;
    }
    this->ants.clear();
    scl::square_delete(this->position);
}
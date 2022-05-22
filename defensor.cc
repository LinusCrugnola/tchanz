/******************************************************************************!
* @file     defensor.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#include "defensor.h"

#include <iostream>

#include "message.h"

Defensor::Defensor(scl::csquare position, unsigned age, unsigned hill_index)
    : Ant(position, hill_index, false), age(age) {
    scl::square_add(position);
}

bool Defensor::action(scl::csquare hill_pos, bool free){
    this->age++;
    if(age >= bug_life){ 
        this->end_of_life = true;
        return true;
    }
    this->kill_collector();
    if(!this->move(hill_pos)) this->end_of_life = true;
    this->kill_collector();
    return true;
}

bool Defensor::move(scl::csquare hill_pos){
    scl::square new_pos = this->position;
    bool success = false;
    //try to go up:
    new_pos = new_pos + this->direction;
    success |= this->verify_position(new_pos, hill_pos);
    if(success) return true;
    for(unsigned i = 0; i < 3; i++){
        new_pos = this->position;
        this->direction.rotate90();
        new_pos = new_pos + this->direction;
        success |= this->verify_position(new_pos, hill_pos);
        if(success) return true;
    }
    return success;
}

bool Defensor::verify_position(scl::csquare new_pos, scl::csquare hill_pos){
    if(!scl::square_contains(hill_pos, this->position)){
        scl::square new_pos = this->position;
        scl::vector back = this->direction;
        back.rotate90();
        back.rotate90();
        new_pos += back;
        if(scl::square_contains(hill_pos, new_pos) &&
           !scl::square_superposition(new_pos)){
            scl::square_delete(this->position);
            this->position = new_pos;
            scl::square_add(this->position);
            return true;
        }
        return false;
    }
    if(scl::square_contains(hill_pos, this->position) && 
       !scl::square_contains(hill_pos, new_pos)){
        return true;
    }
    scl::square_delete(this->position);
    if(scl::square_validation(new_pos, scl::NOERR) && 
       !scl::square_superposition(new_pos) &&
       scl::square_contains(hill_pos, new_pos)){
        this->position = new_pos;
        scl::square_add(this->position);
        return true;
    }
    scl::square_add(this->position);
    return false;
}

void Defensor::kill_collector(){
    for(auto& hill : predatables){
        for(auto& coll : hill){
            if(coll->get_hill() == this->hill_index) break;
            scl::square pos = coll->get_position();
            if(pos.side != 3) continue;
            if(scl::square_touch(this->position, pos)){
                coll->kill();
            }
        }
    }
}

bool Defensor::draw(graphic::color color) {
    return scl::square_draw(this->position, scl::cross, color);
}

Ant* Defensor::data_validation(std::istringstream& data,
                               scl::csquare anthill_position,
                               const unsigned& home) {
    Ant* defensor = nullptr;
    scl::square position = {0, 0, sizeD, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age))
        std::cout << "reading error!" << std::endl;

    if (!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        scl::square overlap = scl::square_get_superposition(position);
        std::cout << message::defensor_overlap(position.x, position.y,
                                               overlap.x, overlap.y);
        return nullptr;
    }

    if (!scl::square_contains(anthill_position, position)) {
        std::cout << message::defensor_not_within_home(position.x, position.y, home);
        return nullptr;
    }

    defensor = new Defensor(position, age, home);
    return defensor;
}

std::string Defensor::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
                + std::to_string(this->position.y) + " " 
                + std::to_string(this->age) + "\n";
}
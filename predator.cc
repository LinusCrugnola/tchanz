/******************************************************************************!
* @file     predator.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#include "predator.h"

#include <iostream>

#include "message.h"

Predator::Predator(scl::csquare position, unsigned age, unsigned hill_index)
    : Ant(position, hill_index, true), age(age), heading_home(true){
    scl::square_add(position);
}

bool Predator::action(scl::csquare hill_pos, bool free){
    this->kill_touching();
    scl::square target = this->set_target(hill_pos, free);
    if(target.x != this->position.x || target.y != this->position.y){
        this->move(target);
        this->kill_touching();
    }
    return true;
}

void Predator::kill_touching(){
    for(auto& predatable : this->predatables){
        for(auto& pred : predatable){
            if(pred == nullptr) continue;
            if(this->hill_index == pred->get_hill()) break;
            if(scl::square_touch(pred->get_position(), this->position)){
                pred->kill();
            }
        }
    }
}

scl::square Predator::set_target(scl::square hill_pos, bool free){
    double distance = 1000;
    unsigned xc = hill_pos.x + hill_pos.side/2;
    unsigned yc = hill_pos.y + hill_pos.side/2;
    scl::square target = {xc, yc, 1, 1};
    bool changed = false;
    if(free){    
        for(auto& predatable : this->predatables){
            for(auto& pred : predatable){
                if(pred == nullptr) continue;
                if(this->hill_index == pred->get_hill()) break;
                if(scl::distance(pred->get_position(), this->position) < distance &&
                   scl::square_contains(hill_pos, pred->get_position())){
                    distance = scl::distance(pred->get_position(), this->position);
                    target = pred->get_position();
                    changed = true;
                }
            }
        }
        this->heading_home = changed ? false : true;
        return target;
    }
    else{
        for(auto& predatable : this->predatables){
            for(auto& pred : predatable){
                if(pred == nullptr) continue;
                if(this->hill_index == pred->get_hill()) break;
                if(scl::distance(pred->get_position(), this->position) < distance){
                    distance = scl::distance(pred->get_position(), this->position);
                    target = pred->get_position();
                }
            }
        }
        this->heading_home = false;
        return target;
    }
}

void Predator::move(scl::csquare target){
    scl::vector direction = {(int) target.x - (int) this->position.x, 
                             (int) target.y - (int) this->position.y};
    if(abs(direction.dx) >= abs(direction.dy)){
        direction.dx = direction.dx * 2 / abs(direction.dx);
        direction.dy = direction.dy / abs(direction.dy);
    }
    else{
        direction.dy = direction.dy * 2 / abs(direction.dy);
        direction.dx = direction.dx / abs(direction.dx);
    }
    scl::square new_pos = this->position;
    new_pos += direction;
    if(!heading_home) scl::square_delete(target);
    if(scl::square_validation(new_pos, scl::NOERR) && 
       !scl::square_superposition(new_pos)){
        scl::square_delete(this->position);
        this->position = new_pos;
        scl::square_add(this->position);
    }
    if(!heading_home) scl::square_add(target);
}

bool Predator::draw(graphic::color color) {
    return scl::square_draw(this->position, scl::uniform, color);
}

Ant* Predator::data_validation(std::istringstream& data, unsigned hill_index) {
    Ant* predator = nullptr;
    scl::square position = {0, 0, sizeP, 1};
    unsigned age;
    if (!(data >> position.x >> position.y >> age))
        std::cout << "reading error!" << std::endl;

    if (!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        std::cout << message::predator_overlap(position.x, position.y);
        return nullptr;
    }

    predator = new Predator(position, age, hill_index);
    return predator;
}

std::string Predator::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
                + std::to_string(this->position.y) + " "
                + std::to_string(this->age) + "\n";
}
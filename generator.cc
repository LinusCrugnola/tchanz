/******************************************************************************!
* @file     generator.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
* @version  1.0
* @date     12.04.2022
*******************************************************************************/

#include "generator.h"

#include <iostream>

#include "message.h"

Generator::Generator(scl::csquare position, double total_food, unsigned hill_index)
    : Ant(position, hill_index, false), total_food(total_food) {
    scl::square_add(position);
    this->predatables.push_back({});
}

bool Generator::action(scl::csquare hill_pos, bool free){
    // check position
    if(!this->move(hill_pos)){
        this->end_of_life = true;
        return false;
    }
    // consume nutrition
    if((this->total_ants * food_rate) >= total_food) 
        return false;
    else 
        this->total_food -= this->total_ants * food_rate;
    return true;
}

bool Generator::move(scl::csquare hill_pos) {
    unsigned xc = hill_pos.x + hill_pos.side / 2;
    unsigned yc = hill_pos.y +hill_pos.side / 2;
    scl::square new_pos = this->position;
    bool success = false;
    if (new_pos.x < xc)
        new_pos.x++;
    else if (new_pos.x > xc)
        new_pos.x--;
    if (new_pos.y < yc)
        new_pos.y++;
    else if (new_pos.y > yc)
        new_pos.y--;
    success |= this->verify_position(new_pos, hill_pos);
    if(success) return true;
    if(this->verify_position(this->position, hill_pos)) return true;
    new_pos = this->position;
    new_pos.x++;
    success |= this->verify_position(new_pos, hill_pos);
    if(success) return true;
    new_pos = this->position;
    new_pos.x--;
    success |= this->verify_position(new_pos, hill_pos);
    if(success) return true;
    new_pos = this->position;
    new_pos.y++;
    success |= this->verify_position(new_pos, hill_pos);
    if(success) return true;
    new_pos = this->position;
    new_pos.y--;
    success |= this->verify_position(new_pos, hill_pos);
    if(success) return true;
    return false;
}

bool Generator::verify_position(scl::csquare new_pos, scl::csquare hill_pos){
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

void Generator::set_total_ants(unsigned total) {
    this->total_ants = total;
}

bool Generator::draw(graphic::color color) {
    return scl::square_draw(this->position, scl::uniform, color);
}

void Generator::add_food(unsigned food) {
    this->total_food += food * val_food;
}

Generator* Generator::data_validation(scl::coord xg, scl::coord yg,
                                      scl::csquare anthill_position,
                                      const unsigned& home, unsigned total_food) {
    scl::square position = {xg, yg, sizeG, 1};

    if (!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        scl::square overlap = scl::square_get_superposition(position);
        std::cout << message::generator_overlap(position.x, position.y, overlap.x,
                                                overlap.y);
        return nullptr;
    }

    if (!scl::square_contains(anthill_position, position)) {
        std::cout << message::generator_not_within_home(position.x, position.y, home);
        return nullptr;
    }

    Generator* generator = new Generator(position, total_food, home);
    return generator;
}

std::string Generator::get_filedata() {
    return std::to_string(this->position.x) + " " + std::to_string(this->position.y);
}
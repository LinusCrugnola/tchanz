/******************************************************************************!
 * @file     ants.cc
 * @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
 *           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
 * @version  2.0
 * @date     01.04.2022
 *******************************************************************************/

#include "ant.h"

#include <iostream>
#include <string>

#include "constantes.h"
#include "message.h"
#include "squarecell.h"

std::vector<std::vector<Ant*>> Ant::predatables = {{}};

Ant::Ant(scl::csquare position, unsigned hill_index, bool predatable = false)
    : position(position), end_of_life(false), hill_index(hill_index) {
    scl::square_add(position);
    if(predatable){
        if(hill_index >= this->predatables.size()){
            this->predatables.push_back({this});
        }
        else{
            this->predatables[hill_index].push_back(this);
        }
    }
}

void Ant::kill(){
    this->end_of_life = true;
}

Ant::~Ant() {
    scl::square_delete(this->position);
    size_t index = 0;
    for(size_t i = 0; i < predatables[hill_index].size(); i++){
        if(this->position == predatables[hill_index][i]->get_position()){
            index = i;
            break;
        }
    }
    predatables[hill_index].erase(predatables[hill_index].begin() + index);
}
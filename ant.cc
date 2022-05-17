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
#include <vector>

#include "constantes.h"
#include "message.h"
#include "squarecell.h"

/**
 * @brief table to store all predatable ants (known by predator)
 * 
 * @details contains all collector and predator ants of a hill with the index that the 
 * hill obtains at creation
 */
namespace{
    std::vector<std::vector<Ant*>> predatables;
}

Ant::Ant(scl::csquare position, unsigned hill_index, bool predatable = false)
    : position(position), end_of_life(false), hill_index(hill_index) {
    scl::square_add(position);
    if(predatable){
        if(hill_index >= predatables.size()){
            //std::vector<Ant*> new_fam = {this}; 
            predatables.push_back({this});
        }
        else{
            predatables[hill_index].push_back(this);
        }
    }
};

Ant::~Ant() {
    scl::square_delete(this->position);
}
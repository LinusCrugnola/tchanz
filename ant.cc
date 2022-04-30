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

Ant::Ant(scl::csquare position)
    : position(position), end_of_life(false) {
    scl::square_add(position);
};

Ant::~Ant() {
    scl::square_delete(this->position);
}
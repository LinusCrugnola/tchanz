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

Generator::Generator(scl::csquare position)
    : Ant(position) {
    scl::square_add(position);
}

bool Generator::action(scl::csquare hill_pos){
    return true;
}

bool Generator::draw(graphic::color color) {
    return scl::square_draw(this->position, scl::uniform, color);
}

Ant* Generator::data_validation(scl::coord xg, scl::coord yg,
                                scl::csquare anthill_position,
                                const unsigned& home) {
    Ant* generator = nullptr;
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

    generator = new Generator(position);
    return generator;
}

std::string Generator::get_filedata() {
    return std::to_string(this->position.x) + " " + std::to_string(this->position.y);
}
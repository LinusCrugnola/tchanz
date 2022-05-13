/******************************************************************************!
 * @file     nutrition.cc
 * @author   Léo Brückl <leo.bruckl@epfl.ch>             70 %
 *           Linus Crugnola <linus.crugnola@epfl.ch>     30 %
 * @version  1.0
 * @date     01.04.2022
 *******************************************************************************/

#include "nutrition.h"

#include <iostream>
#include <math.h>

#include "message.h"

bool Nutrition::add_element(std::istringstream& data) {
    bool valid = true;
    scl::square position = {0, 0, 1, 1};
    if (!(data >> position.x >> position.y))
        return false;

    valid = scl::square_validation(position); // displays error if invalid

    if (scl::square_superposition(position)) {
        std::cout << message::food_overlap(position.x, position.y);
        valid = false;
    }

    if (valid) {
        //add element to map
        //block square

        //temp
        scl::square_add(position);
        this->foods.push_back(position);
        return true;
    }
    return false;
}

bool Nutrition::add_element(unsigned x, unsigned y){
    scl::square position = {x, y, 1, 1};

    if(!scl::square_validation(position) || scl::square_superposition(position))
        return false;

    scl::square_add(position);
    this->foods.push_back(position);
    return true;
}

unsigned Nutrition::get_nbF(){
    return this->foods.size();
}

bool Nutrition::draw_all() {
    for (const auto& elem : this->foods) {
        //draw white rhombs
        if (!scl::square_draw(elem, scl::rhomb, {1, 1, 1})) return false;
    }
    return true;
}

std::string Nutrition::get_filedata() {
    std::string output = {};
    output += "# \n\n";
    output += "# nb food\n" + std::to_string(this->foods.size()) + "\n\n# food \n";
    for (auto elem : this->foods) {
        output += std::to_string(elem.x) + "  " + std::to_string(elem.y) + "\n";
    }
    return output;
}

scl::square Nutrition::get_nearest(scl::csquare pos_collector)
{
    unsigned int distance(0);
    unsigned int closest(0);
    scl::square food_target;
    for (const auto& elem : this->foods)
    {
       if(check_diagonal(pos_collector,elem))
       {
           int vx(0), vy(0);
           vx = elem.x - this->pos_collector.x; // add this->pos_collector.x ?
           vy = elem.y - this->pos_collector.y; // add this->pos_collector.y ?
           distance = std::max(abs(vx),abs(vy));
           if(closest == 0)
           {
               closest = distance;
           }
           else if(distance < closest)
           {
               closest = distance;
               food_target = elem;
           }
       }
    }
    return food_target;
}

void Nutrition::clear() {
    for (auto elem : foods) {
        scl::square_delete(elem);
    }
    this->foods.clear();
}

Nutrition::~Nutrition() {
    for (auto elem : this->foods) {
        scl::square_delete(elem);
    }
    this->foods.clear();
}
/******************************************************************************!
* @file     collector.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             10 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     90 %
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#include "collector.h"

#include <iostream>
#include <math.h>

#include "message.h"

Collector::Collector(scl::csquare position, unsigned age, Etat_collector food_state, 
                     Nutrition* nutrition, unsigned hill_index)
    : Ant(position, hill_index, true), age(age), food_state(food_state), 
      nutrition(nutrition) {
    scl::square_add(position);
}

Collector::~Collector(){
    scl::square_delete(this->position);
    if(this->food_state == LOADED){
        this->nutrition->add_element(this->position.x, this->position.y);
    }
}

bool Collector::action(scl::csquare hill_pos, bool free){
    age++;
    if(age >= bug_life){ 
        this->end_of_life = true;
        return true;
    }

    scl::square target = this->nutrition->get_nearest(this->position);

    scl::vector step = get_step(target);

    verify_position(step);

    return true;
}

unsigned Collector::count_superpos(scl::vector prim, unsigned steps1, 
                            scl::vector sec, unsigned steps2){
    scl::square mock = this->position;
    unsigned count = 0;
    for(unsigned i = 0; i < steps1; i++){
        mock += prim;
        if(scl::square_superposition(mock)) count++;
    }
    for(unsigned i = 0; i < steps2; i++){
        mock += sec;
        if(scl::square_superposition(mock)) count++;
    }
    return count;
}

scl::vector Collector::get_step(scl::csquare target){
    int vx = target.x - this->position.x;
    int vy = target.y - this->position.y;
    unsigned avx = abs(vx);
    unsigned avy = abs(vy);
    if(avx == avy) return {vx/avx, vy/avy};
    else if(avx > avy){
        unsigned s1 = count_superpos({vx/avx, vy/avy}, avx - avy, 
                                     {vx/avx, -vy/avy}, avy - avx);
        unsigned s2 = count_superpos({vx/avx, -vy/avy}, avy - avx, 
                                     {vx/avx, vy/avy}, avx - avy);
        if(s1 > s2) return {vx/avx, vy/avy};
        else if(s1 < s2) return {vx/avx, -vy/avy};
        //TODO: case equals
    }
    else{
        unsigned s1 = count_superpos({vy/avy, vx/avy}, avy - avx, 
                                     {vy/avy, -vx/avx}, avx - avy);
        unsigned s2 = count_superpos({vy/avy, -vx/avx}, avx - avy, 
                                     {vy/avy, vx/avy}, avy - avx);
        if(s1 > s2) return {vx/avx, vy/avy};
        else if(s1 < s2) return {vx/avx, -vy/avy};
        //TODO: case equals
    }
}

bool Collector::verify_position(scl::cvector step){
    scl::square_delete(this->position);
    scl::square new_position = this->position + step;
    if(scl::square_validation(new_position) && 
       !scl::square_superposition(new_position)){
        this->position = new_position;
        scl::square_add(this->position);
        return true;
    }
    scl::square_add(this->position);
    return false;
}

bool Collector::draw(graphic::color color) {
    bool no_error = true;
    no_error = scl::square_draw(this->position, scl::diagonal, color);
    if (this->food_state == LOADED) {
        scl::square_draw({this->position.x, this->position.y, 1, 1}, 
                          scl::rhomb, {1, 1, 1});
    }
    return no_error;
}

bool Collector::loaded() const { return this->food_state == LOADED ? true : false; }

Ant* Collector::data_validation(std::istringstream& data, Nutrition* nutrition,  
                                unsigned hill_index) {
    Ant* collector = nullptr;
    scl::square position = {0, 0, sizeC, 1};
    unsigned age;
    std::string food;
    Etat_collector food_state;
    if (!(data >> position.x >> position.y >> age >> food))
        std::cout << "reading error!" << std::endl;
    food_state = food == "true" ? LOADED : EMPTY;

    if (!scl::square_validation(position)) return nullptr;

    if (scl::square_superposition(position)) {
        scl::square overlap = scl::square_get_superposition(position);
        std::cout << message::collector_overlap(position.x, position.y,
                                                overlap.x, overlap.y);
        return nullptr;
    }

    collector = new Collector(position, age, food_state, nutrition, hill_index);
    return collector;
}

std::string Collector::get_filedata(){
    return "\t" + std::to_string(this->position.x) + " " 
           + std::to_string(this->position.y) + " " + std::to_string(this->age) + " "
           + (this->food_state == LOADED ? "true" : "false") + "\n";
}
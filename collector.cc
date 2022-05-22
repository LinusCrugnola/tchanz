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
      unload_next_move(false), nutrition(nutrition) {
    scl::square_add(position);
}

Collector::~Collector(){
    scl::square_delete(this->position);
    if(this->food_state == LOADED){
        this->nutrition->add_element(this->position.x, this->position.y);
    }
}

bool Collector::action(scl::csquare hill_pos, bool free){
    static unsigned no_move_count = 0;
    if(unload_next_move){
        this->food_state = EMPTY;
        this->unload_next_move = false;
    }
    age++;
    if(age >= bug_life){ 
        this->end_of_life = true;
        return true;
    }
    scl::square target;
    if(this->food_state == EMPTY)
        target = this->nutrition->get_nearest(this->position);
    else{ //loaded
        target = {hill_pos.x + hill_pos.side/2, 
                              hill_pos.y + hill_pos.side/2, 1, 1};
        if(!scl::check_diagonal(target, this->position)) target.x++;
    }
    if(target == this->position){    
        if(scl::square_contains(hill_pos, this->position)){
            if(!this->leave_home(hill_pos))
            return true;
        }
        else return true;
    }
    scl::path path = this->get_path(target);
    scl::vector step = this->get_step(path);
    if(!this->verify_position(step, target, true)){
        no_move_count++;
    }
    if(this->food_state == EMPTY && scl::square_superposition(this->position, target)){
        if(this->nutrition->delete_element(target))
            this->food_state = LOADED;
    }
    else if(this->food_state == LOADED && scl::square_touch(hill_pos, this->position))
        this->unload_next_move = true;
    if(no_move_count >= 4){
        this->move_unblock();
        no_move_count = 0;
    }
    return true;
}

scl::path Collector::get_path(scl::csquare target){
    int vx = target.x - this->position.x;
    int vy = target.y - this->position.y;
    int avx = abs(vx);
    int avy = abs(vy);
    if(avx == avy) return {{ vx/avx,  vy/avy}, avx, {0,0}, 0};
    if(avx > avy) return {{ vx/avx, 1}, (avx + vy)/2, { vx/avx, -1}, (avx - vy)/2};
    else return {{1,  vy/avy}, (avy + vx)/2, {-1,  vy/avy}, (avy - vx)/2};
}

scl::vector Collector::get_step(scl::path path){
    if(path.steps2 == 0) return path.dir1;
    unsigned deviation1 = 0, deviation2 = 0;
    unsigned count1 = this->count_superpos(path, deviation1);
    unsigned count2 = this->count_superpos(scl::permute(path), deviation2);
    if(count1 < count2){
        return ((int)deviation1 == path.steps1 ? path.dir2 : path.dir1);
    }
    else if(count1 > count2){
        return ((int)deviation2 == path.steps2 ? path.dir1 : path.dir2);
    }
    else{
        count1 = this->get_first_superpos(path, deviation1);
        count2 = this->get_first_superpos(scl::permute(path), deviation2);
        if(count1 >= count2){
            return ((int)deviation1 == path.steps1 ? path.dir2 : path.dir1);
        }
        else{
            return ((int)deviation2 == path.steps2 ? path.dir1 : path.dir2);
        }
    }
}

unsigned Collector::count_superpos(scl::path path, unsigned& deviation){
    scl::square mock = this->position;
    bool no_modif = true;
    unsigned count = 0;
    for(int i = 0; i < path.steps1; i++){
        if(no_modif){
            scl::square test_square = mock;
            no_modif = scl::square_validation(test_square + path.dir1, scl::NOERR);
            if(!no_modif) deviation++;
        }
        else deviation++;
        mock += (no_modif ? path.dir1 : path.dir2);
        if(scl::square_superposition(mock)) count++;
    }
    for(unsigned i = 0; i < deviation; i++){
        mock += path.dir1;
        if(scl::square_superposition(mock)) count++;
    }
    for(unsigned i = 0; i < path.steps2 - deviation; i++){
        mock += path.dir2;
        if(scl::square_superposition(mock)) count++;
    }
    return count;
}

unsigned Collector::get_first_superpos(scl::path path, unsigned deviation){
    scl::square mock = this->position;
    unsigned count = 0;
    for(unsigned i = 0; i < path.steps1 - deviation; i++){
        mock += path.dir1;
        if(scl::square_superposition(mock)) return count;
        count++;
    }
    for(unsigned i = 0; i < deviation; i++){
        mock += path.dir2;
        if(scl::square_superposition(mock)) return count;
        count++;
    }
    for(unsigned i = 0; i < deviation; i++){
        mock += path.dir1;
        if(scl::square_superposition(mock)) return count;
        count++;
    }
    for(unsigned i = 0; i < path.steps1 - deviation; i++){
        mock += path.dir2;
        if(scl::square_superposition(mock)) return count;
        count++;
    }
    return count;
}

bool Collector::verify_position(scl::cvector step, scl::csquare target, bool chasing){
    scl::square_delete(this->position);
    if(chasing && food_state == EMPTY) scl::square_delete(target);
    scl::square new_pos = this->position;
    new_pos += step;
    if(scl::square_validation(new_pos, scl::NOERR) 
       && !scl::square_superposition(new_pos)){
        this->position = new_pos;
        if(chasing && food_state == EMPTY) scl::square_add(target);
        scl::square_add(this->position);
        return true;
    }
    if(chasing && food_state == EMPTY) scl::square_add(target);
    scl::square_add(this->position);
    return false;
}

bool Collector::leave_home(scl::csquare hill_pos){
    scl::vector direction;
    if(this->position.x > hill_pos.x + hill_pos.side/2){
        direction.dx = 1;
    }
    else if(this->position.x < hill_pos.x + hill_pos.side/2){
        direction.dx = -1;
    }
    else direction.dx = this->position.x < scl::g_max/2 ? 1 : -1;

    if(this->position.y > hill_pos.y + hill_pos.side/2){
        direction.dy = 1;
    }
    else if(this->position.y < hill_pos.y + hill_pos.side/2){
        direction.dy = -1;
    }
    else direction.dy = this->position.y < scl::g_max/2 ? 1 : -1;

    return this->verify_position(direction, this->position, false);    
}

bool Collector::move_unblock(){
    scl::vector direction = {1,1};

    bool success = false;

    success |= this->verify_position(direction, this->position, false);
    if(success) return true;
    direction.rotate90();
    success |= this->verify_position(direction, this->position, false);
    if(success) return true;
    direction.rotate90();
    success |= this->verify_position(direction, this->position, false);
    if(success) return true;
    direction.rotate90();
    success |= this->verify_position(direction, this->position, false);
    if(success) return true;
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
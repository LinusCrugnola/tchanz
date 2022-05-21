/******************************************************************************!
* @file     anthill.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             90 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     10 %
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include "anthill.h"

#include <iostream>
#include <math.h>

#include "message.h"

unsigned Anthill::anthill_count = 0;

Anthill::Anthill(scl::csquare position, cunsigned nbC, cunsigned nbD, cunsigned nbP)
    : position(position), nbC(nbC), nbD(nbD), nbP(nbP), anthill_state(FREE), 
      end_of_klan(false), highlight(false), generator(nullptr), 
      index(Anthill::anthill_count++){
    this->color = scl::get_new_color();
}

bool Anthill::draw_hill() {
    return scl::square_draw(this->position, scl::empty, this->color, this->highlight);
}

bool Anthill::draw_ants() {
    this->generator->draw(this->color);
    for (const auto& ant : this->ants) {
        if (!ant->draw(this->color)) return false;
    }
    return true;
}

Anthill* Anthill::anthill_validation(std::istringstream& data,
                                     std::vector<Anthill*>& hills_existing, 
                                     cunsigned home) {
    Anthill* anthill = nullptr;
    scl::square position = {0, 0, 0, 0};
    unsigned xg, yg;
    unsigned total_food;
    unsigned nbC, nbD, nbP;
    if (!(data >> position.x >> position.y >> position.side >> xg >> yg >> total_food
               >> nbC >> nbD >> nbP)) {
        std::cout << "reading error!" << std::endl;
    }

    if (!scl::square_validation(position)) return nullptr;

    for (unsigned i(0); i < hills_existing.size(); i++) {
        if (scl::square_superposition(hills_existing[i]->get_position(), position)) {
            std::cout << message::homes_overlap(i, hills_existing.size());
            return nullptr;
        }
    }

    anthill = new Anthill(position, nbC, nbD, nbP);

    Generator* generator = Generator::data_validation(xg, yg, position, home, 
                                                      total_food);
    if(generator != nullptr)
        anthill->generator = generator;
    else
        return nullptr;

    return anthill;
}

unsigned Anthill::get_ants() const {
    return this->nbC + this->nbD + this->nbP + 1;
}

bool Anthill::generator_action(std::default_random_engine* engine, Nutrition* food) {
    // updatde food and ants in generator:
    this->generator->add_food(get_new_food());
    this->generator->set_total_ants(get_ants());

    // consume food
    if(!this->generator->action(this->position, false))
        this->end_of_klan = true;
    
    // generate ants:
    if(!this->end_of_klan){
        std::bernoulli_distribution b(std::min(1.0, 
                                      this->generator->get_total_food()*birth_rate));
        if(b(*engine)){
            this->create_ant(food);
        }
    }
    //delete this->ants.back();
    return true; 
}

bool Anthill::ants_action() const {
    bool free = this->anthill_state == FREE ? true : false;
    for(unsigned i = 0; i < this->ants.size(); i++){
        this->ants[i]->action(this->position, free);
    }
    return true;
}

unsigned Anthill::get_new_food() const {
    unsigned new_nutrition = 0;
    for(unsigned i = 0; i < this->nbC && i < this->ants.size() ; i++){
        if(scl::square_touch(this->position, this->ants[i]->get_position())){
            if(this->ants[i]->loaded()){
                new_nutrition++;
            }
        }
    }
    return new_nutrition;
}

bool Anthill::create_ant(Nutrition* food){
    scl::square pos = scl::get_free3x3(this->position);
    std::cout << "spawn at: " << pos.x << " " << pos.y << " " << pos.side << std::endl;
    double prop_coll, prop_def;
    if(this->anthill_state == FREE){
        prop_coll = prop_free_collector;
        prop_def = prop_free_defensor;
    }
    else{
        prop_coll = prop_constrained_collector;
        prop_def = prop_constrained_defensor;
    }
    if(((double) this->nbC / this->get_ants()) < prop_coll){
        if(pos.side != 3) return false;
        this->ants.insert(this->ants.begin() + this->nbC, 
                          new Collector(pos, 0, EMPTY, food, index));
        this->nbC++;
        return true;
    }
    else if(((double) this->nbD / this->get_ants()) < prop_def){
        if(pos.side != 3) return false;
        this->ants.insert(this->ants.begin() + this->nbC + this->nbD,
                          new Defensor(pos, 0, index));
        this->nbD++;
        return true;
    }
    else{
        pos.side = pos.side == 3 ? 1 : pos.side;
        if(pos.side != 1) return false;
        this->ants.push_back(new Predator(pos, 0, index));
        this->nbP++;
        return true;
    }
    return false;
}

bool Anthill::ant_validation(std::istringstream& data, cunsigned home, 
                             Nutrition* nutrition) {
    static unsigned i = 0, total = this->get_ants() - 1;
    if(i == 0)
        total = this->get_ants() - 1;
    bool reset = false;
    Ant* new_ant = nullptr;
    if(i < this->nbC)
        new_ant = Collector::data_validation(data, nutrition, home);
    else if(i < this->nbC + this->nbD)
        new_ant = Defensor::data_validation(data, this->position, home);
    else if(i < total)
        new_ant = Predator::data_validation(data, home);
    else 
        reset = true;
    if(new_ant != nullptr){
        this->ants.push_back(new_ant);
        i++;
        return true;
    }
    else{
        i = 0;
        total = 0;
    }
    return reset;
}

void Anthill::remove_dead_ants(){
    unsigned temp_nbC = this->nbC;
    unsigned temp_nbD = this->nbD;
    for(unsigned i = 0; i < this->ants.size(); i++){
        if(this->ants[i]->is_dead()){
            delete this->ants[i];
            this->ants[i] = nullptr;

            if(i < temp_nbC) this->nbC--;
            else if(i < temp_nbC + temp_nbD) this->nbD--;
            else this->nbP--;
        }
    }
    this->ants.erase(std::remove(this->ants.begin(), this->ants.end(), nullptr), 
                                 this->ants.end());
}

void Anthill::set_highlight() {
    this->highlight = true;
}

void Anthill::delete_highlight() {
    this->highlight = false;
}

std::string Anthill::get_filedata(unsigned home) {
    std::string output = {};
    std::string gen_dat = this->generator->get_filedata();
    // add anthill data
    output +=  "\t" +  std::to_string(this->position.x) 
              + " " +  std::to_string(this->position.y) 
              + " " +  std::to_string(this->position.side) + " " + gen_dat
              + " " +  std::to_string((int) this->generator->get_total_food())
              + " " +  std::to_string(this->nbC) + " " +  std::to_string(this->nbD)
              + " " +  std::to_string(this->nbP);
    output += " # anthill #" +  std::to_string(home) + "\n";
    // add ant data
    for(unsigned i=1; i<=nbC; i++){
        if(i == 1) output += "\n\t# collectors:\n";
        output += this->ants[i]->get_filedata();
    }
    for(unsigned i=nbC+1; i<=nbD+nbC; i++){
        if(i == nbC+1) output += "\n\t# defensors:\n";
        output += this->ants[i]->get_filedata();
    }
    for(unsigned i=nbD+nbC+1; i<=this->get_ants()-1; i++){
        if(i == nbD+nbC+1) output += "\n\t# predators:\n";
        output += this->ants[i]->get_filedata();
    }
    return output;
}

std::string Anthill::get_info(){
    std::string food_count = std::to_string(this->generator->get_total_food());
    unsigned pos = food_count.find(".");
    return "Total Food: " + food_count.substr(0, pos + 3) + "\n\n" +
           "nbC: " + std::to_string(this->nbC) + "\n" +
           "nbD: " + std::to_string(this->nbD) + "\n" +
           "nbP: " + std::to_string(this->nbP) + 
           "                            \n";
}

bool Anthill::check_growth(std::vector<Anthill*>& hills){
    unsigned new_size = sqrt(4 * (pow(sizeG, 2) + pow(sizeC, 2)*this->nbC 
                          + pow(sizeD, 2)*this->nbD + pow(sizeP, 2)*this->nbP));
    if(new_size < this->position.side){
        this->anthill_state = FREE;
    }
    else if(this->anthill_state == CONSTRAINED) return false;
    //check top right corner expansion
    scl::square new_position = this->position;
    new_position.side = new_size + 2;
    if(this->update_position(new_position, hills)) return true;
    //check botton right corner expansion
    new_position = this->position;
    new_position.side = new_size + 2;
    new_position.y -= new_position.side - position.side;
    if(this->update_position(new_position, hills)) return true;
    //check botton left corner expansion
    new_position = this->position;
    new_position.side = new_size + 2;
    new_position.x -= new_position.side - position.side;
    new_position.y -= new_position.side - position.side;
    if(this->update_position(new_position, hills)) return true;
    //check top left corner expansion
    new_position = this->position;
    new_position.side = new_size + 2;
    new_position.x -= new_position.side - position.side;
    if(this->update_position(new_position, hills)) return true;
    this->anthill_state = CONSTRAINED;
    return false;
}

bool Anthill::update_position(scl::csquare new_position, std::vector<Anthill*>& hills){
    if(!scl::square_validation(new_position, scl::NOERR)) return false;
    unsigned superpos_count = 0;
    for(const auto& hill : hills){
        if(scl::square_superposition(new_position, hill->get_position()))
            superpos_count++;
    }
    if(superpos_count < 2){
        this->position = new_position;
        return true;
    }
    return false;
}

Anthill::~Anthill() {
    // destroy all ants
    delete this->generator;
    for (auto& ant : this->ants) {
        delete ant;
        ant = nullptr;
    }
    this->ants.clear();
    scl::square_delete(this->position);
}
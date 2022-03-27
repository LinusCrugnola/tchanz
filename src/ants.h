/****************************************************************!
 \file     ants.h
 \author   Léo Brückl, Linus Crugnola
 \date     25.03.2022
 \brief    ants interface
*****************************************************************/
 
#ifndef ANTS_H
#define ANTS_H

#include <string>
#include <sstream>

#include "squarecell.h"
#include "constantes.h"

class Ant
{
private:
    square position;
public:
    static Ant data_validation(std::istringstream data);
    Ant(square position) : position(position){
        square_add(position);
    };

    // debug function:
    virtual square print_data(Ant& ant);
};

// Subclasses of ant:
class Generator : public Ant
{
private:
    /* data */
public:
    static Generator data_validation(std::istringstream data);
};

class Collector : public Ant
{
private:
    Etat_collector food;
    unsigned age;
public:
    static Collector data_validation(std::istringstream data);
    Collector(square position, unsigned age, Etat_collector food)
    : position(position), age(age), food(food){
        square_add(position);
    }
};

class Defensor : public Ant
{
private:
    unsigned age;    
public:
    static Defensor data_validation(std::istringstream data);
    Defensor(square position, unsigned age) : position(position), age(age){
        square_add(position);
    }
};

class Predator : public Ant
{
private:
    unsigned age;
public:
    static Predator data_validation(std::istringstream data);
    Predator(square position, unsigned age) : position(position), age(age){
        square_add(position);
    }
};


#endif
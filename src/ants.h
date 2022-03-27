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
    unsigned age;
public:
    static Ant data_validation(std::istringstream data);
    Ant(square position) : position(position){};

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
    Generator(square postion) : position(position){
        square_add(position);
    }
};

class Collector : public Ant
{
private:
    Etat_collector food;
public:
    static Collector data_validation(std::istringstream data);
    Collector(square position, unsigned age, Etat_collector food)
    : position(position), age(age), food(food){
        square_add(posit)
    }
};

class Defensor : public Ant
{
private:
    /* data */
public:
    static Defensor data_validation(std::istringstream data);
    Defensor(square position, unsigned age) : position(position), age(age){}
};

class Predator : public Ant
{
private:
    /* data */
public:
    /* data */
};


#endif
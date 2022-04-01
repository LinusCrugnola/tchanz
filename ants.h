/******************************************************************************!
* @file     ants.h
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/
 
#ifndef ANTS_H
#define ANTS_H

#include <string>
#include <sstream>

#include "squarecell.h"
#include "constantes.h"

// Base class ant:
class Ant
{
    protected:
        square position;
    public:
        Ant(square position) : position(position){
            square_add(position);
        };
};

// Subclasses of ant:
class Generator : public Ant
{
    private:
        /* data */
    public:
        static Ant* data_validation(unsigned xg, unsigned yg, const square& anthill_position, const unsigned& home);
        Generator(square position) : Ant(position){
            square_add(position);
        }
};

class Collector : public Ant
{
private:
    unsigned age;
    Etat_collector food;
public:
    static Ant* data_validation(std::istringstream& data);
    Collector(square position, unsigned age, Etat_collector food)
    : Ant(position), age(age), food(food){
        square_add(position);
    }
};

class Defensor : public Ant
{
private:
    unsigned age;    
public:
    static Ant* data_validation(std::istringstream& data, const square& anthill_position, const unsigned& home);
    Defensor(square position, unsigned age) : Ant(position), age(age){
        square_add(position);
    }
};

class Predator : public Ant
{
private:
    unsigned age;
public:
    static Ant* data_validation(std::istringstream& data);
    Predator(square position, unsigned age) : Ant(position), age(age){
        square_add(position);
    }
};


#endif
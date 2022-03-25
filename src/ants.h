/****************************************************************!
 \file     ants.h
 \author   Léo Brückl, Linus Crugnola
 \date     25.03.2022
 \brief    ants interface
*****************************************************************/
 
#ifndef ANTS_H
#define ANTS_H

#include <string>

#include "squarecell.h"

class Ant
{
private:
    square square;
    unsigned age;
public:
    static Ant data_validation(std::string line);
    Ant(square square) : square(square){};

    // debug function:
    virtual square print_data(Ant& ant);
};

// Subclasses of ant:
class Generator : public Ant
{
private:
    /* data */
public:
    /* data */
};

class Collector : public Ant
{
private:
    /* data */
public:
    /* data */
};

class Defensor : public Ant
{
private:
    /* data */
public:
    /* data */
};

class  : public Ant
{
private:
    /* data */
public:
    /* data */
};


#endif
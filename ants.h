/******************************************************************************!
 * @file     ants.h
 * @author   Léo Brückl <leo.bruckl@epfl.ch>
 *           Linus Crugnola <linus.crugnola@epfl.ch>
 * @version  1.0
 * @date     01.04.2022
 *******************************************************************************/

#ifndef ANTS_H
#define ANTS_H

#include <sstream>

#include "squarecell.h"
#include "constantes.h"

/**
 * @class Ant
 * @brief Base class of ants
 */
class Ant {
protected:
    square position;

public:
    /**
     * @brief Construct a new Ant object
     * 
     * @param position 2D coordinates (center) and side length
     */
    Ant(square position);
};

/**
 * @class Generator
 * @brief Subclass of ant
 * 
 * @note Each anthill has a Generator that stays inside of the hill
 */
class Generator : public Ant {
public:

    /**
     * @brief validates that an ants position is inside the hill and it doesn't 
     * intersect with another entity
     * @param coordinates, position of anthill and number of anthill 
     * @returns pointer to new ant object
     */
    static Ant* data_validation(unsigned xg, unsigned yg, const square& 
                                anthill_position, const unsigned& home);

    /**
     * @brief Construct a new Generator object
     * 
     * @param position 2D coordinates (center) and side length
     */
    Generator(square position);
};

/**
 * @class Collector
 * @brief Subclass of ant
 * 
 * @note Collector ants search and carry food
 */
class Collector : public Ant {
private:
    unsigned age;
    Etat_collector food;

public:
    /**
     * @brief validates that an ants position is inside the grid and it doesn't 
     * intersect with another entity
     * @param input data stream
     * @returns pointer to new ant object
     */
    static Ant* data_validation(std::istringstream& data);

    /**
     * @brief Construct a new Collector object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age 
     * @param food a collector can initially be empty or loaded
     */
    Collector(square position, unsigned age, Etat_collector food);
};

/**
 * @class Defensor
 * @brief Subclass of ant
 * 
 * @note Defensor ants defend the anthill
 */
class Defensor : public Ant {
private:
    unsigned age;

public:
    /**
     * @brief validates that an ants position is inside the hill and it doesn't 
     * intersect with another entity
     * @param input data stream, position and number of anthill
     * @returns pointer to new ant object
     */
    static Ant* data_validation(std::istringstream& data, const square& 
                                anthill_position, const unsigned& home);

    /**
     * @brief Construct a new Defensor object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age 
     */
    Defensor(square position, unsigned age);
};

/**
 * @class Predator
 * @brief Subclass of ant
 * 
 * @note At simulation initialization, predators must be inside the anthill
 * @note Preadator ants atack other anthills
 */
class Predator : public Ant {
private:
    unsigned age;

public:
    /**
     * @brief validates that an ants position is inside the grid and it doesn't 
     * intersect with another entity
     * @param input data stream
     * @returns pointer to new ant object
     */
    static Ant* data_validation(std::istringstream& data);

    /**
     * @brief Construct a new Predator object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age 
     */
    Predator(square position, unsigned age);
};

#endif
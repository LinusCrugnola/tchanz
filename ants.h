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

    /**
     * @brief Destroy the Ant object
     * 
     * @note Frees the square occupied by the ant
     */
    virtual ~Ant();
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
     * 
     * @param xg x coordinate of generator
     * @param yg y cooridinate of generator
     * @param anthill_position position of the parent anthill
     * @param home number of parent anthill (starts at 0)
     * 
     * @returns pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(coord xg, coord yg, csquare 
                                anthill_position, const unsigned& home);

    /**
     * @brief Construct a new Generator object
     * 
     * @param position 2D coordinates (center) and side length
     */
    Generator(csquare position);
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
     * 
     * @param input data stream
     * 
     * @returns pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data);

    /**
     * @brief Construct a new Collector object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     * @param food a collector can initially be empty or loaded
     */
    Collector(csquare position, unsigned age, Etat_collector food);
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
     * 
     * @param input data stream, position and number of anthill
     * 
     * @returns pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data, csquare 
                                anthill_position, const unsigned& home);

    /**
     * @brief Construct a new Defensor object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     */
    Defensor(csquare position, unsigned age);
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
     * 
     * @param input data stream
     * 
     * @returns pointer to new ant object, null if position is invalid
     */
    static Ant* data_validation(std::istringstream& data);

    /**
     * @brief Construct a new Predator object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     */
    Predator(csquare position, unsigned age);
};

#endif
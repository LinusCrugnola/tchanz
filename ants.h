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
    scl::square position;

public:
    /**
     * @brief Construct a new Ant object
     * 
     * @param position 2D coordinates (center) and side length
     */
    Ant(scl::csquare position); 
    
    /**
     * @brief Get the configfile data of an ant object
     * 
     * @return std::string 
     */
    virtual std::string get_filedata() = 0;

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
    static Ant* data_validation(scl::coord xg, scl::coord yg, scl::csquare 
                                anthill_position, const unsigned& home);

    /**
     * @brief get the configfile data of a generator
     * 
     * @return std::string with x and y coordinate
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Generator object
     * 
     * @param position 2D coordinates (center) and side length
     */
    Generator(scl::csquare position);
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
     * @brief get the configfile data of a collector
     * 
     * @return std::string with coordinates, age and state
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Collector object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     * @param food a collector can initially be empty or loaded
     */
    Collector(scl::csquare position, unsigned age, Etat_collector food);
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
    static Ant* data_validation(std::istringstream& data, scl::csquare 
                                anthill_position, const unsigned& home);

    /**
     * @brief get the configfile data of a defensor
     * 
     * @return std::string with coordinates and age
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Defensor object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     */
    Defensor(scl::csquare position, unsigned age);
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
     * @brief get the configfile data of a predator
     * 
     * @return std::string with coordinates and age
     */
    std::string get_filedata();

    /**
     * @brief Construct a new Predator object
     * 
     * @param position 2D coordinates (center) and side length
     * @param age initial age of the ant
     */
    Predator(scl::csquare position, unsigned age);
};

#endif
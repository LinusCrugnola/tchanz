/******************************************************************************!
* @file     defensor.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     12.04.2022
*******************************************************************************/
 
#ifndef DEFENSOR_H
#define DEFENSOR_H

#include <sstream>
#include <string>

#include "squarecell.h"
#include "constantes.h"
#include "ant.h"

class Ant;

/**
 * @class Defensor
 * @brief Subclass of ant
 * 
 * @note Defensor ants defend the anthill
 */
class Defensor : public Ant {
private:
    /**
     * @brief age of the ant
     */
    unsigned age;

    /**
     * @brief vector to memorize the direction in which the defensor walks
     * @remark default is up because ants spawn first in top right corner
     */
    scl::vector direction = {0, 1};

    /**
     * @brief verifies if a new position is valid and changes the position if true
     * 
     * @param new_pos new position
     * @param hill_pos position of the anthill
     * @return true if position is valid
     */
    bool verify_position(scl::csquare new_pos, scl::csquare hill_pos);

    /**
     * @brief move the defensor ant
     * 
     * @param hill_pos position of anthill
     * @return true if it could move without leaving the anthill
     */
    bool move(scl::csquare hill_pos);

    /**
     * @brief kill collectors that are in contact with the defensor ant
     */
    void kill_collector();

public:
    /**
     * @brief move the defensor ant
     * 
     * @param hill_pos position of the hill
     * @param free indicates if the hill can grow
     * @return true if no errors
     */
    virtual bool action(scl::csquare hill_pos, bool free) override;

    /**
     * @brief draw the defensor ant
     * @remark draws a square with a cross inside
     * 
     * @param color specifies the color of the ant (parent color)
     * @return true if no errors
     */
    virtual bool draw(graphic::color color) override;

    /**
     * @brief validate the configfile data and return ant if valid
     * 
     * @param data position and number of anthill (stream)
     * @param anthill_position position of the hill
     * @param home index of the home anthill
     * @return pointer to new ant object, null if position is invalid
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
     * @param hill_index index of the parent anthill
     */
    Defensor(scl::csquare position, unsigned age, unsigned hill_index);
};

#endif /* DEFENSOR_H */

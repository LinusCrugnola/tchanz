/******************************************************************************!
* @file     squarecell.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

/**
 * @brief General type square
 * 
 * @param x coordinate of point
 * @param y coordinate of point
 * @param side length of square
 * @param centered true if point is in the center of square, false if point is the 
 * lower left corner of square
 */
struct square {
    unsigned x;
    unsigned y;
    unsigned side;
    bool centered;
};

constexpr short unsigned g_dim = 7;
constexpr short unsigned g_max = 128;

/**
 * @brief Validation of a square checks if square is inside of the grid borders
 * 
 * @note function throws error if square is not valid
 * 
 * @returns bool: true if square is valild
 */
bool square_validation(square square);

/**
 * @brief Checks if a square superposes with an existing square in the grid
 * 
 * @returns Bool: true if there's a superposition
 */
bool square_superposition(square square);

/**
 * @brief Test if two squares superpose 
 * 
 * @returns Bool: true if there's a superpostion
 */
bool square_superposition(square square1, square square2);

/**
 * @brief get the point where a square superposes in the grid
 * 
 * @returns Gets first point where squares superpose (biggest y, smallest x)
 */
square square_get_superposition(square test);

/**
 * @brief Test if the first square contains a second square
 * 
 * @returns Bool: true if first square fully contains second square
 * 
 * @note the borders of the squares cannot overlap
 */
bool square_contains(square s1, square s2);

/**
 * @brief Add a square to the grid 
 * 
 * @returns Bool: false if a square is invalid or that there's a superposition 
 */
bool square_add(square square);

/**
 * @brief Deletes a square from the grid 
 * 
 * @returns Bool: false if there's no square or square invalid
 */
bool square_delete(square square);

/**
 * @brief Functions to debug the module
 */
void set_coordinate(unsigned x, unsigned y);
void print_grid();

#endif
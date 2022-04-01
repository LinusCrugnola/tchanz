/******************************************************************************!
* @file     squarecell.h
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

struct square {
    unsigned x;
    unsigned y;
    unsigned side;
    /**
     * @brief Centered (point is in the center of square or bottom left edge)
     */
    bool centered;
};

constexpr short unsigned g_dim = 7;
constexpr short unsigned g_max = 128;

/**
 * @brief Validation of a square, function throws error
 */
bool square_validation(square square);

/**
 * @brief Test if a square superposes with an existing square 
 * True if there's a superposition
 */
bool square_superposition(square square);

/**
 * @brief Test if two squares superpose 
 * True if there's a superpostion
 */
bool square_superposition(square square1, square square2);

/**
 * @brief Gets first square that superposes (biggest y, smallest x)
 */
square square_get_superposition(square test);

/**
 * @brief Test if a first square contains a second square
 */
bool square_contains(square s1, square s2);

/**
 * @brief Add a square to the grid 
 * Returns false if a square is invalid or that there's a superposition) 
 */
bool square_add(square square);

/**
 * @brief Deletes a square from the grid 
 * Returns false if there's no square or square invalid)
 */
bool square_delete(square square);

// Functions to test module
void set_coordinate(unsigned x, unsigned y);
void print_grid();

#endif
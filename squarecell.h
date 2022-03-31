/******************************************************************************!
* @file     squarecell.h
* @author   Léo Brückl, Linus Crugnola
* @version  1.0
*******************************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

// Concrete type square
struct square {
    // coordinates (point)
    unsigned x;
    unsigned y;
    // side length
    unsigned side;
    // centered (point is in the center of square or bottom left edge)
    bool centered;
};

// module constants
constexpr short unsigned g_dim = 7;
constexpr short unsigned g_max = 128;

// Validation of a square, function throws error
bool square_validation(square square);

// Test if a square superposes with an existing square (true if superposition)
bool square_superposition(square square);

// Test if two squares superpose (true if superposition)
bool square_superposition(square square1, square square2);

// get first square that superposes (biggest y, smallest x)
square square_get_superposition(square test);

// Test if first square contains second square
bool square_contains(square s1, square s2);

// Add a square to the grid (returns false if square invalid or superposition)
bool square_add(square square);

// Delete a square from the grid (returns false if no square or square invalid)
bool square_delete(square square);

// Functions to test module
void set_coordinate(unsigned x, unsigned y);
void print_grid();

#endif
/****************************************************************!
	\file     squarecell.h
	\author   Léo Brückl, Linus Crugnola
	\date     22.03.2022
	\brief    squarecell interface
*****************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

#include <math.h>

// module constants
constexpr short unsigned g_dim = 7;
constexpr short unsigned g_max = 128;

// Concrete type square
struct square{
    // coordinates (point)
    unsigned x;
    unsigned y;
    // side length
    unsigned side;
    // centered (point is in the center of square or bottom left edge)
    bool centered;
};

// Validation of a square (returns false if square invalid)
bool square_validation(square square);

// Test if a square superposes with an existing square (true if superposition)
bool square_superposition(square square);
bool square_superposition(square square1, square square2);

// Add a square to the grid (returns false if square invalid or superposition)
bool square_add(square square);

// Delete a square from the grid (returns false if no square or square invalid)
bool square_delete(square square);

// Functions to test module
void set_coordinate(unsigned x, unsigned y);
void print_grid();

#endif
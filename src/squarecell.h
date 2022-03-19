/****************************************************************!
	\file     squarecell.h
	\author   Léo Brückl, Linus Crugnola
	\date     18.03.2022
	\brief    squarecell interface
*****************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

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

void square_validation_test(square square);
bool square_superposition_test(square square);
bool square_add(square square);
bool square_delete(square square);

// Functions to test module
void set_coordinate(unsigned x, unsigned y);
void print_grid();

#endif
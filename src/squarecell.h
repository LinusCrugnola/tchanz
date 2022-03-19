/****************************************************************!
	\file     squarecell.h
	\author   Léo Brückl, Linus Crugnola
	\date     18.03.2022
	\brief    squarecell interface
*****************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

void square_validation_test(unsigned x, unsigned y, unsigned side, bool centered);
bool square_superposition_test(unsigned x, unsigned y, unsigned side, bool centered);
bool square_add(unsigned x, unsigned y, unsigned side, bool centered);
bool square_delete(unsigned x, unsigned y, unsigned side, bool centered);
void set_coordinate(unsigned x, unsigned y);
void print_grid();
unsigned get_gmax();

#endif
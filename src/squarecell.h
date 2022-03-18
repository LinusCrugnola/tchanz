/****************************************************************!
  \file     squarecell.h
  \author   Léo Brückl, Linus Crugnola
  \date     date
  \brief    squarecell interface
*****************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

//Class definition (raw) as proposition
// class Squarecell
// {
// private:
//     unsigned g_max;
//     std::vector<std::vector<bool>> grid;
// public:
//     Squarecell(uint g_max);
//     void square_validation(unsigned x, unsigned y, unsigned side, bool centered);
//     bool square_superposition(unsigned x, unsigned y, unsigned side, bool centered);
//     bool square_add(unsigned x, unsigned y, unsigned side, bool centered);
//     bool square_delete(unsigned x, unsigned y, unsigned side, bool centered);
// };

// Function to check if a square is valid (fits in the grid):
void square_validation(unsigned x, unsigned y, unsigned side, bool centered);

// Function to check if a square superposes with existing squares in the grid:
bool square_superposition(unsigned x, unsigned y, unsigned side, bool centered);

// Add a square to the grid:
bool square_add(unsigned x, unsigned y, unsigned side, bool centered);

// Delete a square from the grid
bool square_delete(unsigned x, unsigned y, unsigned side, bool centered);

#endif
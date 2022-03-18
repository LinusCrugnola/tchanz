#ifndef SQUARECELL_H
#define SQUARECELL_H

// Function to check if a square is valid (fits in the grid):
void square_validation(unsigned x, unsigned y, unsigned side, bool centered);

// Function to check if a square superposes with existing squares in the grid:
bool square_superposition(unsigned x, unsigned y, unsigned side, bool centered);

#endif
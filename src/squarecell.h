/****************************************************************!
  \file     squarecell.h
  \author   Léo Brückl, Linus Crugnola
  \date     18.03.2022
  \brief    squarecell interface
*****************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

#include <vector>

class Squarecell
{
private:
    unsigned g_max;
    std::vector<std::vector<bool>> grid;
public:
    Squarecell(unsigned max)
    : g_max(max){
      std::vector<std::vector<bool>> _grid(max, std::vector<bool>(max));
      this->grid = _grid;
    };
    void square_validation_test(unsigned x, unsigned y, unsigned side, bool centered);
    bool square_superposition_test(unsigned x, unsigned y, unsigned side, bool centered);
    bool square_add(unsigned x, unsigned y, unsigned side, bool centered);
    bool square_delete(unsigned x, unsigned y, unsigned side, bool centered);
    void set_coordinate(unsigned x, unsigned y);
    void print_grid();
    unsigned get_gmax();
};


#endif
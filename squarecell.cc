/******************************************************************************!
* @file     squarecell.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             50 %
*           Linus Crugnola <linus.crugnola@epfl.ch>     50 %
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include "squarecell.h"

#include <iostream>
#include <vector>
#include <array>

#include "error_squarecell.h"

/**
 * @brief unnamed namespace with the implementation of the grid
 */
namespace {
    std::vector<std::vector<bool>> grid(scl::g_max, std::vector<bool>(scl::g_max, 
                                                                      false));
}

bool scl::square_validation(scl::csquare square) {
    if (square.x < 0 || square.x > (scl::g_max-1)) {
        std::cout << error_squarecell::print_index(square.x, scl::g_max-1);
        return false;
    }
    else if (square.y < 0 || square.y > (scl::g_max-1)) {
        std::cout << error_squarecell::print_index(square.y, scl::g_max-1);
        return false;
    }
    if (square.centered) {
        if (square.side % 2 == 0) {
            return false;
        }
        else if ((square.x-square.side/2) < 0 || 
                 (square.x+square.side/2) > scl::g_max-1) {
            std::cout << error_squarecell::print_outside(square.x, square.side,
                                                         scl::g_max-1);
            return false;
        }
        else if ((square.y-square.side/2) < 0 || 
                 (square.y+square.side/2) > scl::g_max-1) {
            std::cout << error_squarecell::print_outside(square.y, square.side,
                                                         scl::g_max-1);
            return false;
        }
    }
    else {
        if ((square.x+square.side-1) > scl::g_max-1) {
            std::cout << error_squarecell::print_outside(square.x, square.side,
                                                         scl::g_max-1);
            return false;
        }
        else if ((square.y+square.side-1) > scl::g_max-1) {
            std::cout << error_squarecell::print_outside(square.y, square.side,
                                                         scl::g_max-1);
            return false;
        }
    }
    return true;
}

bool scl::square_superposition(scl::csquare square) {
    if (square.centered) {
        for (unsigned i = square.y-square.side/2; i <= square.y+square.side/2; i++) {
            for (unsigned j = square.x-square.side/2; j <= square.x+square.side/2;
                 j++) {
                if (grid[j][scl::g_max-1-i]) {
                    return true;
                }
            }
        }
    }
    else {
        for (unsigned i = square.y; i < square.y+square.side; i++) {
            for (unsigned j = square.x; j < square.x+square.side; j++) {
                if (grid[j][scl::g_max-1-i]) {
                    return true;
                }
            }
        }
    }
    return false;
}

scl::square scl::square_get_superposition(scl::csquare test) {
    square cross;
    if (test.centered) {
        for (unsigned i = test.y+test.side/2; i >= test.y-test.side/2; i--) {
            for (unsigned j = test.x-test.side/2; j <= test.x+test.side/2; j++) {
                if (grid[j][scl::g_max-1-i]) {
                    cross = {j, i, 1, 1};
                    return cross;
                }
            }
        }
    }
    else {
        for (unsigned i = test.y+test.side-1; i >= test.y; i--) {
            for (unsigned j = test.x; j < test.x+test.side; j++) {
                if (grid[j][scl::g_max-1-i]) {
                    cross = {j, i, 1, 1};
                    return cross;
                }
            }
        }
    }
    // default return
    return {500, 500, 0, 0};
}

bool scl::square_superposition(scl::csquare s1, scl::csquare s2) {
    // check x
    int xmin, x1min, x2min;
    x1min = s1.centered ? s1.x-s1.side/2 : s1.x;
    x2min = s2.centered ? s2.x-s2.side/2 : s2.x;
    int xmax;
    if (x1min < x2min) {
        xmin = x2min;
        xmax = s1.centered ? s1.x+s1.side/2 : s1.x+s1.side-1;
    }
    else {
        xmin = x1min;
        xmax = s2.centered ? s2.x+s2.side/2 : s2.x+s2.side-1;
    }
    if (xmax >= xmin) {
        // check y
        int ymin, y1min, y2min;
        y1min = s1.centered ? s1.y-s1.side/2 : s1.y;
        y2min = s2.centered ? s2.y-s2.side/2 : s2.y;
        int ymax;
        if (y1min < y2min) {
            ymin = y2min;
            ymax = s1.centered ? s1.y+s1.side/2 : s1.y+s1.side-1;
        }
        else {
            ymin = y1min;
            ymax = s2.centered ? s2.y+s2.side/2 : s2.y+s2.side-1;
        }
        if (ymax >= ymin) {
            return true;
        }
    }
    return false;
}

bool scl::square_contains(scl::csquare s1, scl::csquare s2) {
    if (s2.x-s2.side/2 <= s1.x)
        return false;
    else if (s2.x+s2.side/2 >= s1.x+s1.side-1)
        return false;
    else if (s2.y-s2.side/2 <= s1.y)
        return false;
    else if (s2.y+s2.side/2 >= s1.y+s1.side-1)
        return false;
    return true;
}

bool scl::square_add(scl::csquare square) {
    if (!scl::square_validation(square)) return false;
    if (square.centered) {
        for (unsigned i = square.y-square.side/2; i <= square.y+square.side/2; i++) {
            for (unsigned j = square.x-square.side/2; j <= square.x+square.side/2;
                 j++) {
                grid[j][scl::g_max-1-i] = true;
            }
        }
    }
    else {
        for (unsigned i = square.y; i < square.y+square.side; i++) {
            for (unsigned j = square.x; j < square.x+square.side; j++) {
                grid[j][scl::g_max-1-i] = true;
            }
        }
    }
    return true;
}

bool scl::square_delete(scl::csquare square) {
    if (!scl::square_validation(square)) return false;
    if (square.centered) {
        for (unsigned i = square.y-square.side/2; i <= square.y+square.side/2; i++) {
            for (unsigned j = square.x-square.side/2; j <= square.x+square.side/2;
                 j++) {
                if (!grid[j][scl::g_max-1-i]) return false;
            }
        }
        for (unsigned i = square.y-square.side/2; i <= square.y+square.side/2; i++) {
            for (unsigned j = square.x-square.side/2; j <= square.x+square.side/2;
                 j++) {
                grid[j][scl::g_max-1-i] = false;
            }
        }
    }
    else {
        for (unsigned i = square.y; i < square.y+square.side; i++) {
            for (unsigned j = square.x; j < square.x+square.side; j++) {
                if (!grid[j][scl::g_max-1-i]) return false;
            }
        }
        for (unsigned i = square.y; i < square.y+square.side; i++) {
            for (unsigned j = square.x; j < square.x+square.side; j++) {
                grid[j][scl::g_max-1-i] = false;
            }
        }
    }
    return true;
}

bool scl::square_draw(scl::csquare square, scl::drawtype dtype, graphic::color color, 
                      bool highlight){
    if(!square_validation(square)) 
        return false;
    switch (dtype)
    {
    case empty:
        return graphic::draw_empty(square.x, square.y, square.side, square.centered,
                                   color, highlight);
    case rhomb:
        return graphic::draw_rhomb(square.x, square.y, square.side, square.centered,
                                   color);
    case uniform:
        return graphic::draw_uniform(square.x, square.y, square.side, square.centered, 
                                     color);
    case diagonal:
        return graphic::draw_diagonal(square.x, square.y, square.side,
                                      square.centered, color);
    case cross:
        return graphic::draw_cross(square.x, square.y, square.side, square.centered, 
                                    color);
    default:
        return false;
    }
}

graphic::color scl::get_new_color(bool reset){
    return graphic::get_new_color(reset);
}

// print function (Debug):
void scl::print_grid() {
    for (unsigned i = 0; i < scl::g_max; i++) {
        std::cout << std::endl;
        for (unsigned j = 0; j < scl::g_max; j++) {
            if (grid[j][i]) {
                std::cout << "\033[41;1mO\033[0m";
            }
            else {
                std::cout << "\033[42;1mX\033[0m";
            }
        }
    }
    std::cout << std::endl
              << "_____________" << std::endl;
}
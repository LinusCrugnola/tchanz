/******************************************************************************!
* @file     squarecell.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

#include <iostream>

#include "graphic.h"

/**
 * @brief Squarecell library namespace: scl
 */
namespace scl {
    /**
     * @brief Constants of the module
     */
    constexpr short unsigned g_dim = 7;
    constexpr short unsigned g_max = 128;

    /**
     * @brief flag to print no error message
     */
    constexpr bool NOERR = false;

    /**
     * @brief General type vector that gives a direction
     * 
     * @param dx change of x direction
     * @param dy change of y direciton
     */
    struct vector {
        int dx;
        int dy;

        /**
         * @brief function to rotate the vector 90° to the right
         */
        void rotate90();
    };

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

        square operator+=(const vector& vec);
    };

    /**
     * @brief Define drawing types for squares
     * 
     * @details empty:    empty square (only border line)
     *          rhomb:    square border with a rhomb inscribed
     *          uniform:  completely filled square
     *          diagonal: square with diagonals inscribed (X)
     *          cross:   square with a grid form inscribed (#)
     */
    enum drawtype {empty, rhomb, uniform, diagonal, cross};

    /**
     * @brief define a constant reference on square
     */
    typedef const square& csquare;

    /**
     * @brief define a constant reference on vector
     */
    typedef const vector& cvector;

    /**
     * @brief define reference on coordinate
     */
    typedef const unsigned& coord;

    /**
     * @brief Operators on squares & vectors:
     */
    square operator+(square& s, cvector vec);
    std::ostream& operator<<(std::ostream& os, csquare dt);
    std::ostream& operator<<(std::ostream& os, cvector v);

    /**
     * @brief get the distance between two squares
     * 
     * @param s1 
     * @param s2 
     * @return double distance
     */
    double distance(csquare s1, csquare s2);

    /**
     * @brief Validation of a square checks if square is inside of the grid borders
     * 
     * @return true if square is valild
     * 
     * @note function throws error if square is not valid
     */
    bool square_validation(csquare square, bool print = true);

    /**
     * @brief Checks if a square superposes with an existing square in the grid
     * 
     * @return true if there's a superposition
     */
    bool square_superposition(csquare square);

    /**
     * @brief Test if two squares superpose 
     * 
     * @return true if there's a superpostion
     */
    bool square_superposition(csquare square1, csquare square2);

    /**
     * @brief get the point where a square superposes in the grid
     * 
     * @return Gets first point where squares superpose (biggest y, smallest x)
     */
    square square_get_superposition(csquare test);

    /**
     * @brief Test if the first square contains a second square
     * 
     * @return true if first square fully contains second square
     * 
     * @note the borders of the squares cannot overlap
     */
    bool square_contains(csquare s1, csquare s2);

    /**
     * @brief Test to see if two squares are on the same family of diagonals
     * THESE TWO ENTITIES HAVE CENTERED COORDINATES
     * THEY ARE CENTERED SQUARES!!
     * 
     * @param s1 
     * @param s2 
     * @return true 
     * @return false 
     */
    bool check_diagonal(csquare s1, csquare s2);

    /**
     * @brief Test if the squares touch each other (no space between)
     * 
     * @return true if the squares touch 
     */
    bool square_touch(csquare s1, csquare s2);

    /**
     * @brief Get a free 3x3 or 1x1 centered square inside a given non-centered square 
     * 
     * @param space given square to search
     * 
     * @return scl::square free  3x3 square or 1x1 square or {0,0,0,0} 
     * if none available
     */
    scl::square get_free3x3(csquare space);

    /**
     * @brief Add a square to the grid 
     * 
     * @return false if a square is invalid or if there's a superposition 
     */
    bool square_add(csquare square);

    /**
     * @brief Deletes a square from the grid 
     * 
     * @return Bool: false if there's no square or square invalid
     */
    bool square_delete(csquare square);

    /**
     * @brief Draws a square with a chosen drawtype
     * 
     * @param square 
     * @param type 
     * @param highlight square is filled with transparent color (default false)
     * 
     * @return bool true if no errors while drawing
     */
    bool square_draw(csquare square, drawtype type, graphic::color color, 
                     bool highlight = false);

    /**
     * @brief Gets the next color from the graphic module
     * 
     * @note the order of the colors is: red, green, blue, yellow, magenta, cyan
     *       after cyan, it restarts with red.
     * 
     * @param reset flag to reset color if true (restart at red)
     * 
     * @return graphic::color (rgb struct)
     */
    graphic::color get_new_color(bool reset = 0);

    /**
     * @brief Functions to debug the module
     */
    void print_grid();
}

#endif /* SQUARECELL_H */
/******************************************************************************!
* @file     squarecell.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#ifndef SQUARECELL_H
#define SQUARECELL_H

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
     * @brief General type point
     * 
     * @remark this is not used in rendu 2
     * 
     * @param x coordinate of point
     * @param y coordinate of point
     */
    struct point {
        unsigned x;
        unsigned y;
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
     * @brief define a constant reference on square
     */
    typedef const point& cpoint;

    /**
     * @brief define reference on coordinate
     */
    typedef const unsigned& coord;


    /**
     * @brief convert a point to a square
     * 
     * @param point 
     * @return square 
     */
    square to_square(point point);

    /**
     * @brief Validation of a square checks if square is inside of the grid borders
     * 
     * @return true if square is valild
     * 
     * @note function throws error if square is not valid
     */
    bool square_validation(csquare square);

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
     * 
     * @return bool true if no errors while drawing
     */
    bool square_draw(csquare square, drawtype type, graphic::color color);

    /**
     * @brief Gets the next color from the graphic module
     * 
     * @note the order of the colors is: red, green, blue, yellow, magenta, cyan
     *       after cyan, it restarts with red.
     * 
     * @return graphic::color (rgb struct)
     */
    graphic::color get_new_color();

    /**
     * @brief Functions to debug the module
     */
    void print_grid();
}

#endif
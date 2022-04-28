/******************************************************************************!
* @file     graphic.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     22.04.2022
*******************************************************************************/
 
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm/drawingarea.h>

typedef const unsigned& cunsigned;
typedef const double& cdouble;

/**
 * @brief namespace of the graphic module
 */
namespace graphic{
    /**
     * @brief concrete type of rgb color
     */
    struct color {
        double r;
        double g;
        double b;
    };

    /**
     * @brief Gets the next color from the hidden color list
     * 
     * @note the order of the colors is: red, green, blue, yellow, magenta, cyan
     *       after cyan, it restarts with red.
     * 
     * @param reset flag to reset the list if true (restart at red)
     * 
     * @return graphic::color (rgb struct)
     */
    color get_new_color(bool reset);

    /**
     * @brief set the cairo context pointer in graphic module
     * 
     * @param cr cairo context pointer
     */
    void set_context(const Cairo::RefPtr<Cairo::Context>& cr);

    /**
     * @brief draw an empty square (border only)
     * 
     * @remark style of anthill
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square, can't be < 3
     * @param centered true if origin in center, false if bottom left corner
     * @param color graphic::color of the square
     * @param highlight square is filled with transparent color (default false)
     * 
     * @return true if drawing could be done
     */
    bool draw_empty(cunsigned x, cunsigned y, cunsigned side, bool centered, 
                    color color, bool highlight = false);

    /**
     * @brief draw a square with inscribed rhomb (no borders) TODO: verify
     * 
     * @remark style of food
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square
     * @param centered true if origin in center, false if bottom left corner
     * @param color graphic::color of the square
     * 
     * @return true if drawing could be done
     */
    bool draw_rhomb(cdouble x, cdouble y, cdouble side, bool centered, color color);

    /**
     * @brief draw a filled square
     * 
     * @remark style of generator ant
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square
     * @param centered true if origin in center, false if bottom left corner
     * @param color graphic::color of the square
     * 
     * @return true if drawing could be done
     */
    bool draw_uniform(cunsigned x, cunsigned y, cunsigned side, bool centered, 
                      color color);

    /**
     * @brief draw a square and its diagonals (X)
     * 
     * @remark style of the collector ant
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square, must be 3
     * @param centered true if origin in center, false if bottom left corner
     * @param color graphic::color of the square
     * 
     * @return true if drawing could be done
     */
    bool draw_diagonal(cunsigned x, cunsigned y, cunsigned side, bool centered, 
                       color color);

    /**
     * @brief draw a square with inscribed cross (#)
     * 
     * @remark style of the defensor ant
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square, must be 3
     * @param centered true if origin in center, false if bottom left 
     * @param color graphic::color of the square
     * 
     * @return true if drawing could be done
     */
    bool draw_cross(cunsigned x, cunsigned y, cunsigned side, bool centered, 
                    color color);

    /**
     * @brief draw an empty world of size x size (without border)
     * 
     * @param size of the world (scl::g_max)
     * 
     * @return true if world could be drawn
     */
    bool draw_grid(cunsigned size);

    /**
     * @brief draw the border of the world
     * 
     * @param size of the world (scl::g_max)
     * 
     * @return true if the border could be drawn
     */
    bool draw_border(cunsigned size);
}

#endif
#ifndef GRAPHIC_H
#define GRAPHIC_H


typedef const unsigned& cunsigned;

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
     * @returns graphic::color (rgb struct)
     */
    color get_new_color();

    /**
     * @brief draw an empty square (border only)
     * 
     * @remark style of anthill
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square
     * @param centered true if origin in center, false if bottom left corner
     * @return true if drawing could be done
     */
    bool draw_empty(cunsigned x, cunsigned y, cunsigned side, bool centered);

    /**
     * @brief draw a square with inscribed rhomb (no borders) TODO: verify
     * 
     * @remark style of food
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square
     * @param centered true if origin in center, false if bottom left corner
     * @return true if drawing could be done
     */
    bool draw_rhomb(cunsigned x, cunsigned y, cunsigned side, bool centered);

    /**
     * @brief draw a filled square
     * 
     * @remark style of generator ant
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square
     * @param centered true if origin in center, false if bottom left corner
     * @return true if drawing could be done
     */
    bool draw_uniform(cunsigned x, cunsigned y, cunsigned side, bool centered);

    /**
     * @brief draw a square and its diagonals (X)
     * 
     * @remark style of TODO: ?
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square
     * @param centered true if origin in center, false if bottom left corner
     * @return true if drawing could be done
     */
    bool draw_diagonal(cunsigned x, cunsigned y, cunsigned side, bool centered);

    /**
     * @brief draw a square with inscribed grille (#)
     * 
     * @remark style of TODO: ?
     * 
     * @param x x coordinate of square origin
     * @param y y coordinate of square origin
     * @param side side length of square
     * @param centered true if origin in center, false if bottom left corner
     * @return true if drawing could be done
     */
    bool draw_grille(cunsigned x, cunsigned y, cunsigned side, bool centered);
}

#endif
#include "graphic.h"

namespace{
    const graphic::color color_list[6] = {
        {1, 0, 0},   // red
        {0, 1, 0},   // green
        {0, 0, 1},   // blue
        {1, 1, 0.2}, // yellow TODO: try values
        {1, 0, 1},   // magenta
        {0, 1, 1}    // cyan
    };

    const Cairo::RefPtr<Cairo::Context>* ptcr = nullptr;
}

graphic::color graphic::get_new_color(){
    static unsigned state = 0;
    graphic::color new_color = color_list[state];
    state += 1;
    state = state % 6;
    return new_color;
}

bool graphic::draw_empty(cunsigned x, cunsigned y, cunsigned side, bool centered){
    return true;
}

bool graphic::draw_rhomb(cunsigned x, cunsigned y, cunsigned side, bool centered){
    return true;
}
bool graphic::draw_uniform(cunsigned x, cunsigned y, cunsigned side, bool centered){
    return true;
}

bool graphic::draw_diagonal(cunsigned x, cunsigned y, cunsigned side, bool centered){
    return true;
}

bool graphic::draw_grille(cunsigned x, cunsigned y, cunsigned side, bool centered){
    return true;
}
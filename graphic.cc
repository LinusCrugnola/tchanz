/******************************************************************************!
* @file     graphic.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     22.04.2022
*******************************************************************************/
 
#include "graphic.h"

#include <math.h>

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

void graphic::set_context(const Cairo::RefPtr<Cairo::Context>& cr){
    ptcr = &cr;
}

bool graphic::draw_empty(cunsigned x, cunsigned y, cunsigned side, 
                         bool centered, graphic::color color){

    if(side < 3) return false;

    (*ptcr)->set_line_width(0.5);
    (*ptcr)->set_source_rgb(color.r, color.g, color.b);

    //TODO: check line width
    if(centered){
        (*ptcr)->move_to(x-side/2,y-side/2);
        (*ptcr)->line_to(x-side/2,y+side/2);
        (*ptcr)->line_to(x+side/2,y+side/2);
        (*ptcr)->line_to(x+side/2,y-side/2);
        (*ptcr)->line_to(x-side/2-0.25,y-side/2);
        (*ptcr)->stroke();
    }
    else{
        (*ptcr)->move_to(x,y);
        (*ptcr)->line_to(x,y+side-1);
        (*ptcr)->line_to(x+side-1,y+side-1);
        (*ptcr)->line_to(x+side-1,y);
        (*ptcr)->line_to(x-0.25,y);
        (*ptcr)->stroke();
    }
    return true;
}

bool graphic::draw_rhomb(cdouble x, cdouble y, cdouble side, bool centered, 
                         graphic::color color){

    (*ptcr)->set_line_width(sqrt(2)*side/2);
    (*ptcr)->set_source_rgb(color.r, color.g, color.b);

    if(centered){
        (*ptcr)->move_to(x-side/4,y-side/4);
        (*ptcr)->line_to(x+side/4,y+side/4);
        (*ptcr)->stroke();
    }
    else{
        (*ptcr)->move_to(x+side/4-0.5,y+side/4-0.5);
        (*ptcr)->line_to(x+3*side/4-0.5,y+3*side/4-0.5);
        (*ptcr)->stroke();
    }
 
    return true;
}

bool graphic::draw_uniform(cunsigned x, cunsigned y, cunsigned side, bool centered,
                           graphic::color color){

    (*ptcr)->set_line_width(side);
    (*ptcr)->set_source_rgb(color.r, color.g, color.b);

    //TODO: check details (side etc)
    if(centered){
        (*ptcr)->move_to(x-side/2-0.5,y);
        (*ptcr)->line_to(x+side/2+0.5,y);
        (*ptcr)->stroke();
    }
    else{
        (*ptcr)->move_to(x-0.5,y+side/2);
        (*ptcr)->line_to(x+side-0.5,y+side/2);
        (*ptcr)->stroke();
    }
    return true;
}

bool graphic::draw_diagonal(cunsigned x, cunsigned y, cunsigned side, bool centered, 
                            graphic::color color){

    if(side != 3) return false;
    //dark color:
    graphic::color dark = {color.r - 0.5, color.g - 0.5, color.b - 0.5};
    bool even = 0;
    if(centered){
        for(unsigned i = x-side/2; i <= x+side/2; i++){
            for(unsigned j = y-side/2; j <= y+side/2; j++){
                graphic::draw_uniform(i,j,1,1,(even? dark : color));
                even = !even;
            }
        }
    }
    else{
        for(unsigned i = x; i < x+side; i++){
            for(unsigned j = y; j < y+side; j++){
                graphic::draw_uniform(i,j,1,1,(even? dark : color));
                even = !even;
            }
        }
    }
    return true;
}

bool graphic::draw_cross(cunsigned x, cunsigned y, cunsigned side, 
                          bool centered, graphic::color color){

    if(side != 3) return false;
    //dark color:
    graphic::color dark = {color.r - 0.5, color.g - 0.5, color.b - 0.5};
    if(centered){
        for(unsigned i = 0; i < side; i++){
            for(unsigned j = 0; j < side; j++){
                if(i%2 == 1 || j%2 == 1){
                    graphic::draw_uniform(x+i-side/2,y+j-side/2,1,1,color);
                }
                else{
                    graphic::draw_uniform(x+i-side/2,y+j-side/2,1,1,dark);
                }
            }
        }
    }
    else{
        for(unsigned i = 0; i < side; i++){
            for(unsigned j = 0; j < side; j++){
                if(i%2 == 1 || j%2 == 1){
                    graphic::draw_uniform(x+i,y+j,1,1,color);
                }
                else{
                    graphic::draw_uniform(x+i,y+j,1,1,dark);
                }
            }
        }
    }
    return true;
}

bool graphic::draw_grid(cunsigned size){

    (*ptcr)->set_line_width(0.05); //TODO: how large must this be?
    (*ptcr)->set_source_rgb(1,1,1);
    (*ptcr)->translate(-0.5, -0.5);
    //draw lines
    for(unsigned i=0; i<size; i++){
        (*ptcr)->move_to(i,0);
        (*ptcr)->line_to(i,size);
        (*ptcr)->move_to(0,i);
        (*ptcr)->line_to(size,i);
    }
    (*ptcr)->stroke();

    return true;
}

bool graphic::draw_border(cunsigned size){
    //move in case and draw bord
    (*ptcr)->translate(0.5, 0.5);
    (*ptcr)->set_line_width(1);
    (*ptcr)->set_source_rgb(1,1,1);
    (*ptcr)->move_to(0, 0);
    (*ptcr)->line_to(0, size-1);
    (*ptcr)->line_to(size-1, size-1);
    (*ptcr)->line_to(size-1, 0);
    (*ptcr)->line_to(-0.5, 0);

    (*ptcr)->stroke();

    return true;
}
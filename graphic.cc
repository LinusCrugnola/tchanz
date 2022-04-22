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

void graphic::set_context(const Cairo::RefPtr<Cairo::Context>& cr){
    ptcr = &cr;
}

bool graphic::draw_empty(cunsigned x, cunsigned y, cunsigned side, bool centered){

    (*ptcr)->set_line_width(1);
    graphic::color color = get_new_color();
    (*ptcr)->set_source_rgb(color.r, color.g, color.b);

    //draw square
    //TODO: check details (side etc)
    if(centered){
        (*ptcr)->move_to(x-side/2,y-side/2);
        (*ptcr)->line_to(x-side/2,y+side/2);
        (*ptcr)->line_to(x+side/2,y+side/2);
        (*ptcr)->line_to(x+side/2,y-side/2);
        (*ptcr)->line_to(x-side/2,y-side/2);
        (*ptcr)->stroke();
    }
    else{
        (*ptcr)->move_to(x,y);
        (*ptcr)->line_to(x+side,y);
        (*ptcr)->line_to(x+side,y+side);
        (*ptcr)->line_to(x,y+side);
        (*ptcr)->line_to(x,y);
        (*ptcr)->stroke();
    }
    return true;
}

bool graphic::draw_rhomb(cunsigned x, cunsigned y, cunsigned side, bool centered){

    (*ptcr)->set_line_width(1);
    graphic::color color = get_new_color();
    (*ptcr)->set_source_rgb(color.r, color.g, color.b);

    //draw rhomb
    //TODO: check details (side etc)
    if(centered){
        (*ptcr)->move_to(x-side/2,y);
        (*ptcr)->line_to(x,y+side/2);
        (*ptcr)->line_to(x+side/2,y);
        (*ptcr)->line_to(x,y-side/2);
        (*ptcr)->line_to(x-side/2,y);
        (*ptcr)->stroke();
    }
    else{
        (*ptcr)->move_to(x,y+side/2);
        (*ptcr)->line_to(x+side/2,y+side);
        (*ptcr)->line_to(x+side,y+side/2);
        (*ptcr)->line_to(x+side/2,y);
        (*ptcr)->line_to(x,y+side/2);
        (*ptcr)->stroke();          
    }
 
    return true;
}
bool graphic::draw_uniform(cunsigned x, cunsigned y, cunsigned side, bool centered){

    (*ptcr)->set_line_width(side);
    graphic::color color = get_new_color();
    (*ptcr)->set_source_rgb(color.r, color.g, color.b);

    //draw square
    //TODO: check details (side etc)
    if(centered){
        (*ptcr)->move_to(x-side/2,y);
        (*ptcr)->line_to(x+side/2,y);
        (*ptcr)->stroke();
    }
    else{
        (*ptcr)->move_to(x,y+side/2);
        (*ptcr)->line_to(x+side,y+side/2);
        (*ptcr)->stroke();
    }
    return true;
}

bool graphic::draw_diagonal(cunsigned x, cunsigned y, cunsigned side, bool centered){
    return true;
}

bool graphic::draw_grille(cunsigned x, cunsigned y, cunsigned side, bool centered){
    return true;
}

bool graphic::draw_world(cunsigned size, cunsigned width, cunsigned height){

    (*ptcr)->set_line_width(0.05); //TODO: how large must this be?
    (*ptcr)->set_source_rgb(1,1,1);
    //draw lines
    for(unsigned i=0; i<size; i++){
        (*ptcr)->move_to(i,0);
        (*ptcr)->line_to(i,size);
        (*ptcr)->move_to(0,i);
        (*ptcr)->line_to(size,i);
    }
    (*ptcr)->stroke();
    //move in case and draw bord
    (*ptcr)->translate(0.5, 0.5);
    (*ptcr)->set_line_width(1);
    (*ptcr)->move_to(0, 0);
    (*ptcr)->line_to(0, size-1);
    (*ptcr)->line_to(size-1, size-1);
    (*ptcr)->line_to(size-1, 0);
    (*ptcr)->line_to(-1, 0);

    (*ptcr)->stroke();

    return true;
}
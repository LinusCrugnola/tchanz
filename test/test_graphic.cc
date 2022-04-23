#include "testfunctions.h"
#include <cairomm/context.h>
#include "../graphic.h"
#include "../squarecell.h"
#include <iostream>

MockArea::MockArea(){}
MockArea::~MockArea(){}

bool MockArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){

    cr->set_source_rgb(0,0,0);
    cr->paint();

    Gtk::Allocation allocation = get_allocation();
    const double width = allocation.get_width();
    const double height = allocation.get_height();

    //get the ratios
    double scale_y = height/scl::g_max;
    double scale_x = width/scl::g_max;

    // take the smaller ratio to scale 
    double scale = scale_x < scale_y ? scale_x : scale_y;
    cr->translate(0, height);
    cr->scale(scale, -scale);
    cr->translate(0.5,0.5);

    graphic::set_context(cr);

    //set global line width
    cr->set_line_width(1);

    // test drawing functions
    graphic::color color = graphic::get_new_color();
    graphic::draw_empty(2,2,3,1,color);
    color = graphic::get_new_color();
    graphic::draw_empty(4,2,3,0,color);
    color = graphic::get_new_color();
    graphic::draw_empty(6,2,1,1,color);
    color = graphic::get_new_color();
    graphic::draw_empty(8,1,5,0,color);

    color = graphic::get_new_color();
    graphic::draw_rhomb(15,2,1,1,color);
    color = graphic::get_new_color();
    graphic::draw_rhomb(18,2,3,1,color);
    color = graphic::get_new_color();
    graphic::draw_rhomb(21,2,1,0,color);

    color = graphic::get_new_color();
    graphic::draw_uniform(3,8,3,1,color);
    color = graphic::get_new_color();
    graphic::draw_uniform(7,8,5,0,color);
    color = graphic::get_new_color();
    graphic::draw_uniform(14,8,1,1,color);
    color = graphic::get_new_color();
    graphic::draw_uniform(16,8,1,0,color);
    
    color = graphic::get_new_color();
    graphic::draw_diagonal(3,18,3,1,color);
    color = graphic::get_new_color();
    graphic::draw_diagonal(9,18,3,0,color);

    color = graphic::get_new_color();
    graphic::draw_grille(15,18,3,1,color);
    color = graphic::get_new_color();
    graphic::draw_grille(20,18,3,0,color);

    graphic::draw_world(scl::g_max, width, height);

    return true;
}
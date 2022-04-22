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
    // graphic::draw_empty(2,2,3,1);
    // graphic::draw_empty(2,2,3,0);
    // graphic::draw_empty(10,10,1,1);
    // graphic::draw_empty(1,1,5,0);

    // graphic::draw_rhomb(6,6,1,1);
    // graphic::draw_rhomb(10,10,3,1);
    // graphic::draw_rhomb(5,5,1,0);

    // graphic::draw_uniform(3,3,3,1);
    // graphic::draw_uniform(2,2,5,0);
    // graphic::draw_uniform(10,10,1,1);
    // graphic::draw_uniform(11,11,1,0);
    
    graphic::draw_diagonal(2,2,3,1);
    graphic::draw_diagonal(4,4,3,0);

    graphic::draw_grille(8,8,3,1);
    graphic::draw_grille(10,10,3,0);

    graphic::draw_world(scl::g_max, width, height);

    return true;
}
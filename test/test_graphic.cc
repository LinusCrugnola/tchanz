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

    double scalex = width/scl::g_max;
    double scaley = width/scl::g_max;

    //transform to bottom left corner:
    cr->translate(0, height);
    cr->scale(scalex, -3.9);

    graphic::set_context(cr);
    graphic::draw_world(scl::g_max, width, height);

    //set global line width
    cr->set_line_width(1);

    graphic::draw_empty(0,0,30,0);
    graphic::draw_empty(10,10,20,1);
    graphic::draw_rhomb(0,0,30,0);
    graphic::draw_rhomb(10,10,20,1);

    graphic::draw_uniform(50,50,30,1);
    graphic::draw_uniform(35,35,5,0);

    return true;
}
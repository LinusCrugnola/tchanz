#include "testfunctions.h"
#include <cairomm/context.h>
#include "../graphic.h"
#include "../squarecell.h"

MockArea::MockArea(){}
MockArea::~MockArea(){}

bool MockArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    //change coord
    cr->translate(0, height);
    cr->scale(width/(scl::g_max+2), -height/(scl::g_max+2));

    //draw border
    cr->move_to(0,0);
    cr->line_to(0, scl::g_max+2);
    cr->line_to(scl::g_max+2, scl::g_max+2);
    cr->line_to(scl::g_max+2, 0);
    cr->line_to(0, 0);
    cr->stroke();

    //make it smaller
    cr->translate(1,1);

    graphic::set_context(cr);

    graphic::draw_empty(0,0,30,0);
    graphic::draw_empty(10,10,20,1);
    graphic::draw_rhomb(0,0,30,0);
    graphic::draw_rhomb(10,10,20,1);

    return true;
}
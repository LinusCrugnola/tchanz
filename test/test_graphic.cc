#include "testfunctions.h"
#include <cairomm/context.h>
#include "../graphic.h"

MockArea::MockArea(){}
MockArea::~MockArea(){}

bool MockArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    int xc, yc;
    xc = width/2;
    yc = height/2;

    //graphic_set_context(cr);

    return true;
}
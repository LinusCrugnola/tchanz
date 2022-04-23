#include "testfunctions.h"
#include <cairomm/context.h>
#include "../graphic.h"
#include "../squarecell.h"
#include <iostream>
#include"../simulation.h"

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

    graphic::draw_border(scl::g_max);

    //set global line width
    cr->set_line_width(1);


    // // test drawing functions
    // std::cout << "\n------------------------- Test graphic functions ------------------------------" << std::endl;

    // graphic::color color = graphic::get_new_color();
    // graphic::draw_empty(2,2,3,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_empty(4,2,3,0,color);
    // color = graphic::get_new_color();
    // graphic::draw_empty(6,2,1,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_empty(8,1,5,0,color);

    // color = graphic::get_new_color();
    // graphic::draw_rhomb(15,2,1,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_rhomb(18,2,3,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_rhomb(21,2,1,0,color);

    // color = graphic::get_new_color();
    // graphic::draw_uniform(3,8,3,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_uniform(7,8,5,0,color);
    // color = graphic::get_new_color();
    // graphic::draw_uniform(14,8,1,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_uniform(16,8,1,0,color);
    
    // color = graphic::get_new_color();
    // graphic::draw_diagonal(3,18,3,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_diagonal(9,18,3,0,color);

    // color = graphic::get_new_color();
    // graphic::draw_cross(15,18,3,1,color);
    // color = graphic::get_new_color();
    // graphic::draw_cross(20,18,3,0,color);

    // // Test drawing of scl
    // std::cout << "\n------------------------- Test scl::square_draw() ------------------------------" << std::endl;

    // // draw a whole set of figures
    // color = graphic::get_new_color();
    // scl::square_draw({1,30,5,0}, scl::empty, color);
    // color = graphic::get_new_color();
    // scl::square_draw({9,32,5,1}, scl::empty, color);
    // color = graphic::get_new_color();
    // scl::square_draw({15,30,5,0}, scl::uniform, color);
    // color = graphic::get_new_color();
    // scl::square_draw({24,32,5,1}, scl::uniform, color);
    // color = graphic::get_new_color();
    // scl::square_draw({28,32,1,0}, scl::rhomb, color);
    // color = graphic::get_new_color();
    // scl::square_draw({30,32,1,1}, scl::rhomb, color);
    // color = graphic::get_new_color();
    // scl::square_draw({34,31,3,0}, scl::diagonal, color);
    // color = graphic::get_new_color();
    // scl::square_draw({39,32,3,1}, scl::diagonal, color);
    // color = graphic::get_new_color();
    // scl::square_draw({44,31,3,0}, scl::cross, color);
    // color = graphic::get_new_color();
    // scl::square_draw({49,32,3,1}, scl::cross, color);

    std::cout << "\n------------------------- Draw simulation ------------------------------" << std::endl;
    //test simulation
    Simulation simu_test;
    std::cout << "reading output: " << simu_test.read_configfile("testfiles/t01.txt") << std::endl;
    std::cout << "drawing output: " << simu_test.draw_current_state() << std::endl;

    std::cout << "\n------------------------- Draw world ------------------------------" << std::endl;

    graphic::draw_grid(scl::g_max);

    return true;
}
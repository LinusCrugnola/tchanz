#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

/**
 * @file testfunctions.h
 * @author your name (you@domain.com)
 * @brief interface for all tests
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <gtkmm/drawingarea.h>
#include "../simulation.h"

/**
 * @brief example area for drawing
 * 
 */
class MockArea : public Gtk::DrawingArea
{
public:
    MockArea();
    virtual ~MockArea();
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
private:
    Simulation simu;
};


/**
 * @brief test squarecell
 * 
 */
void test_squarecell();

/**
 * @brief test simulation
 * 
 */
void test_simulation();

/**
 * @brief test nutrition
 * 
 */
void test_nutrition();

/**
 * @brief test gui
 * 
 */
void test_gui();

/**
 * @brief test graphic
 * 
 */
void test_graphic();


#endif
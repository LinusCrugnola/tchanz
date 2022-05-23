/******************************************************************************!
* @file     projet.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     100%
* @version  1.0
* @date     01.04.2022
*******************************************************************************/

#include <iostream>
#include <string>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <random>

#include "simulation.h"
#include "gui.h"

#include "squarecell.h"
using namespace std;

/**
 * @brief Main module of Tchanz project (highest priority)
 */

/**
 * @brief project main function
 */
int main(int argc, char **argv){
    //create a simulation and set up the map
    Simulation simulation;

    // get the name of the configfile
    std::string filename = argc > 1 ? argv[1] : "";
    
    simulation.read_configfile(filename);

    //create app without argc and argv (not necessairy)
    auto app = Gtk::Application::create("org.gtkmm.example");
	Gui gui;
    gui.set_simulation(&simulation);
	gui.set_default_size(500,500);
	
	return app->run(gui);
}
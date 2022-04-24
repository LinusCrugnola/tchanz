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

#include "simulation.h"
#include "message.h"
#include "GUIgraphic.h"

/**
 * @brief Main module of Tchanz project (highest priority)
 */

/**
 * @brief state messages
 */
std::string st_read =  "\n----------------- File Lecture ----------------------------";
std::string st_clear = "\n----------------- Abort Lecture ---------------------------";
std::string st_init =  "\n----------------- Initialize Simulation -------------------";
std::string st_empty = "\n----------------- Initialize empty Simulation -------------";

/**
 * @brief project main function
 */
int main(int argc, char **argv){

    //create a simulation and set up the map
    Simulation simulation;

    // get the name of the configfile
    std::cout << st_read << std::endl;
    std::string filename = argc > 1 ? argv[1] : "";
    
    if(!simulation.read_configfile(filename)){
        std::cout << st_clear << std::endl;
        simulation.clear();
        std::cout << st_empty << std::endl;
    }
    else{
        std::cout << message::success();
        std::cout << st_init << std::endl;
    }


    //create app without argc and argv (not necessairy) TODO: verify
    auto app = Gtk::Application::create("org.gtkmm.example");
	Gui gui;
    gui.set_simulation(&simulation);
	gui.set_default_size(800,600);
	
	return app->run(gui);
}
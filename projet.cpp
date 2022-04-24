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

std::string state_read =  "--------------------- File Lecture ----------------------";
std::string state_clear = "--------------------- Abort Lecture ---------------------";
std::string state_init =  "--------------------- Initialize Simulation -------------";
std::string state_write = "--------------------- Generate File ---------------------";


/**
 * @brief project main function
 */
int main(int argc, char **argv){

    //create a simulation and set up the map
    Simulation simulation;

    std::cout << state_read << std::endl;

    // get the name of the configfile
    std::string filename = argc > 1 ? argv[1] : "";
    
    if(!simulation.read_configfile(filename)){
        std::cout << state_clear << std::endl;
        simulation.clear();
    }
    else{
        std::cout << message::success();
    }

    std::cout << state_init << std::endl;

    //create app without argc and argv (not necessairy) TODO: verify
    auto app = Gtk::Application::create("org.gtkmm.example");
	Gui gui(&simulation);
	gui.set_default_size(800,600);
	
	return app->run(gui);
}
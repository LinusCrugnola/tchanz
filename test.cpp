#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "GUIgraphic.h"
#include "graphic.h"
#include "simulation.h"
#include "test/testfunctions.h"


int main(int argc, char** argv){
    std::cout << "\n------------------------- Start tests ------------------------------" << std::endl;
    // std::cout << "\n------------------------- Test squarecell ------------------------------" << std::endl;
    // test_squarecell();
    test_simulation();
    // test_nutrition();
    // std::cout << "\n------------------------- Test GUI ------------------------------" << std::endl;

    // Simulation simu;
    // simu.read_configfile("testfiles/t01.txt");
    
    // auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	// Gui gui(&simu);
	// gui.set_default_size(800,600);
	
	// return app->run(gui);

    // std::cout << "\n------------------------- Test Graphic ------------------------------" << std::endl;
    
    // auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	
    // Gtk::Window win;
    // win.set_title("Test Graphic");
	// win.set_default_size(700,700);

	// MockArea canvas;
    // win.add(canvas);
    // canvas.show();

	// return app->run(win);

    std::cout << "\n------------------------- Finished tests ------------------------------\n" << std::endl;
}

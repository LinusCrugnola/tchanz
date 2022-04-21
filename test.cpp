#include "test/testfunctions.h"
//#include "GUIgraphic.h"
#include "graphic.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include <iostream>

int main(int argc, char** argv){
    std::cout << "\n------------------------- Start tests ------------------------------" << std::endl;
    //std::cout << "\n------------------------- Test squarecell ------------------------------" << std::endl;
    //test_squarecell();
    //test_simulation();
    //test_nutrition();
    // std::cout << "\n------------------------- Test GUI ------------------------------" << std::endl;
    
    // auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	
	// Gui gui;
	// gui.set_default_size(200,200);
	
	// return app->run(gui);

    std::cout << "\n------------------------- Test Graphic ------------------------------" << std::endl;
    
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	
    Gtk::Window win;
    win.set_title("Test Graphic");
	win.set_default_size(200,200);

	MockArea canvas;
    win.add(canvas);
    canvas.show();

	return app->run(win);

    std::cout << "------------------------- Finished tests ------------------------------\n" << std::endl;
}

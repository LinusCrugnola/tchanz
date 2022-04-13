#ifndef GUIGRAPHIC_H
#define GUIGRAPHIC_H

#include <gtkmm.h>

class Canvas
{};

class Gui : public Gtk::Window
{
	public:
		Gui();
		virtual ~Gui();
	
	protected:
		Gtk::Box H_box;
		Gtk::Box navbar;//vertical box
		Gtk::Box display;
		Canvas canvas;
		Gtk::Frame general, info, anthill_info;
		Gtk::Button leave,open;
		
};
		
		



#endif

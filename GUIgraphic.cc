#include <iostream>

#include "GUIgraphic.h"

Gui::Gui()
: 
	H_box(Gtk::ORIENTATION_HORIZONTAL,10),
	navbar(Gtk::ORIENTATION_VERTICAL,5),
	general("General"),
	leave("exit"),
	open("open")
{
	set_title("Tchanz");
	set_border_width(5);
	
	add(H_box);
	
	H_box.pack_start(navbar,Gtk::PACK_SHRINK);
	
	navbar.pack_start(general,Gtk::PACK_SHRINK);
	
	general.add(leave);
	general.add(open);
	
	show_all_children();
}

Gui::~Gui()
{}
	

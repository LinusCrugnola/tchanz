#include <iostream>

#include "GUIgraphic.h"

using namespace std;

Gui::Gui()
: 
	H_box(Gtk::ORIENTATION_HORIZONTAL),
	V_box(Gtk::ORIENTATION_VERTICAL),
	canvas_box(Gtk::ORIENTATION_VERTICAL),
	navbar(Gtk::ORIENTATION_VERTICAL),
	anthill_info_box(Gtk::ORIENTATION_VERTICAL),
	general_frame("General"), info_frame("Info"), anthill_info_frame("Anthill info"),
	nbF_info("Nb food:   nbF"),
	exit("exit"),open("open"),save("save"),start("start"),step("step"),
	previous("previous"), next("next")
{
	set_title("Tchanz");
	set_border_width(5);
	
	add(H_box);
	H_box.pack_start(V_box,Gtk::PACK_SHRINK);
	H_box.pack_start(canvas_box);
	
	canvas_box.pack_start(canvas);
	
	V_box.pack_start(general_frame);
	V_box.pack_start(info_frame);
	V_box.pack_start(anthill_info_frame);
	
	general_frame.add(navbar);
	
	navbar.pack_start(exit);
	navbar.pack_start(open);
	navbar.pack_start(save);
	navbar.pack_start(start);
	navbar.pack_start(step);
	
	info_frame.add(nbF_info);
	
	anthill_info_frame.add(anthill_info_box);
	
	anthill_info_box.pack_start(previous);
	anthill_info_box.pack_start(next);
	
	exit.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_exit) );
	open.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_open) );
	save.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_save) );
	start.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_start) );
	step.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_step) );
	
	show_all_children();
}

Gui::~Gui()
{}

Canvas::Canvas()
{}

Canvas::~Canvas()
{}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) // DESSIN EPFL
{
	
	cr->set_source_rgb(0.92, 0.0, 0.0);
// E
cr->set_line_width(58.0); //~(7/6)50
cr->move_to(50, 50);
cr->line_to(50, 150);
cr->stroke();
cr->move_to(50, 200);
cr->line_to(50, 300);
cr->stroke();
cr->set_line_width(50.0);
cr->move_to(50, 275);
cr->line_to(194, 275);
cr->stroke();
cr->move_to(79, 175);//E milieu
cr->line_to(185, 175);
cr->stroke();
cr->move_to(50, 75);
cr->line_to(194, 75);
cr->stroke();
//P
cr->move_to(250, 50);
cr->line_to(250, 300);
cr->stroke();
cr->move_to(275, 75);
cr->line_to(325, 75);
cr->stroke();
cr->move_to(275, 175);
cr->line_to(325, 175);
cr->stroke();
cr->arc(325, 125, 50, -M_PI/2, M_PI/2);
cr->stroke();
// F
cr->set_line_width(58.0); //~(7/6)50
cr->move_to(450, 50);
cr->line_to(450, 150);
cr->stroke();
cr->move_to(450, 200);
cr->line_to(450, 300);
cr->stroke();
cr->set_line_width(50.0);
cr->move_to(479, 175);//F milieu
cr->line_to(585, 175);
cr->stroke();
cr->move_to(450, 75);
cr->line_to(594, 75);
cr->stroke();
//L
cr->move_to(650, 50);
cr->line_to(650, 300);
cr->stroke();
cr->move_to(650, 275);
cr->line_to(790, 275);
cr->stroke();
return true;
	
}

void Gui::on_button_clicked_exit()
{
	cout << "You have exited the simulation" << endl;
	hide();
}

void Gui::on_button_clicked_open()
{
	//cout << "This button will open a file for the simulation" << endl;
	
	Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}


void Gui::on_button_clicked_save()
{
	cout << "This button will save the current state in a file" << endl;
}

void Gui::on_button_clicked_start()
{
	cout << "This button will start the simulation" << endl;
}

void Gui::on_button_clicked_step()
{
	cout <<  "This button will show the simulation step by step" << endl;
}

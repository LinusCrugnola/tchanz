#include "GUIgraphic.h"

#include <iostream>

#include "graphic.h"

using namespace std;

Gui::Gui()
    : canvas(this),
      H_box(Gtk::ORIENTATION_HORIZONTAL),
      V_box(Gtk::ORIENTATION_VERTICAL),
      canvas_box(Gtk::ORIENTATION_VERTICAL),
      navbar(Gtk::ORIENTATION_VERTICAL),
      anthill_info_box(Gtk::ORIENTATION_VERTICAL),
      general_frame("General"), info_frame("Info"), anthill_info_frame("Anthill info"),
      nbF_info("Nb food:   nbF"),
      exit("exit"), open("open"), save("save"), start("start"), step("step"),
      previous("previous"), next("next"), simulation(nullptr) 
    {
    set_title("Tchanz");
    set_border_width(5);

    add(H_box);
    H_box.pack_start(V_box, Gtk::PACK_SHRINK);
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

    exit.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_exit));
    open.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_open));
    save.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_save));
    start.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_start));
    step.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_step));

    show_all_children();
}

Gui::~Gui() {}

void Gui::update_nbF() {
    if(this->simulation == nullptr){
        this->nbF_info.set_text("Nb food:   0");
    }
    else {
        this->nbF_info.set_text("Nb food:   " + 
                                to_string(this->simulation->get_nbF()));
    }
}

void Gui::draw_simulation_state() {
    if(this->simulation != nullptr)
        this->simulation->draw_current_state();
}

unsigned Gui::get_dimension(){
    if(this->simulation == nullptr) return 128;
    return this->simulation->get_dimension();
}

void Gui::set_simulation(Simulation* simulation){
    this->simulation = simulation;
}

Canvas::Canvas(Gui* parent)
    : parent(parent) {}

Canvas::~Canvas() {}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    unsigned g_max = parent->get_dimension();
    cr->set_source_rgb(0, 0, 0);
    cr->paint();

    Gtk::Allocation allocation = get_allocation();
    const double width = allocation.get_width();
    const double height = allocation.get_height();

    // get the ratios
    double scale_y = height / g_max;
    double scale_x = width / g_max;

    // take the smaller ratio to scale & center
    double scale = scale_x < scale_y ? scale_x : scale_y;
    cr->translate(0, height);
    cr->scale(scale, -scale);
    if (scale_x > scale_y) {
        cr->translate((width - height) / (2 * scale), 0);
    }
    else {
        cr->translate(0, (height - width) / (2 * scale));
    }

    cr->translate(0.5, 0.5);

    graphic::set_context(cr);

    graphic::draw_border(g_max);

    parent->draw_simulation_state();
    parent->update_nbF();

    graphic::draw_grid(g_max);

    return true;
}

void Gui::on_button_clicked_exit() {
    cout << "You have exited the simulation" << endl;
    hide();
}

void Gui::on_button_clicked_open() {
    // cout << "This button will open a file for the simulation" << endl;

    Gtk::FileChooserDialog dialog("Please choose a file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    // Add response buttons the the dialog:
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    // Show the dialog and wait for a user response:
    int result = dialog.run();

    // Handle the response:
    switch (result) {
        case (Gtk::RESPONSE_OK): {
            std::cout << "Open clicked." << std::endl;

            // Notice that this is a std::string, not a Glib::ustring.
            std::string filename = dialog.get_filename();
            std::cout << "File selected: " << filename << std::endl;
            break;
        }
        case (Gtk::RESPONSE_CANCEL): {
            std::cout << "Cancel clicked." << std::endl;
            break;
        }
        default: {
            std::cout << "Unexpected button clicked." << std::endl;
            break;
        }
    }
}

void Gui::on_button_clicked_save() {
    cout << "This button will save the current state in a file" << endl;
}

void Gui::on_button_clicked_start() {
    cout << "This button will start the simulation" << endl;
}

void Gui::on_button_clicked_step() {
    cout << "This button will show the simulation step by step" << endl;
}

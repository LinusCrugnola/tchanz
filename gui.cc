/******************************************************************************!
* @file     gui.cc
* @author   Léo Brückl <leo.bruckl@epfl.ch>             90%
*           Linus Crugnola <linus.crugnola@epfl.ch>     10%
* @version  1.0
* @date     29.04.2022
*******************************************************************************/
 
#include "gui.h"

#include <iostream>

#include "graphic.h"

using namespace std;

/* state message */
const string st_quit = "\n----------------- Exit Program ----------------------";

// Second function larger than 40 lines!
Gui::Gui()
    : canvas(this),
      H_box(Gtk::ORIENTATION_HORIZONTAL),
      V_box(Gtk::ORIENTATION_VERTICAL),
      canvas_box(Gtk::ORIENTATION_VERTICAL),
      navbar(Gtk::ORIENTATION_VERTICAL),
      anthill_info_box(Gtk::ORIENTATION_VERTICAL),
      general_frame("General"), info_frame("Info"), anthill_info_frame("Anthill info"),
      nbF_info("Nb food:   nbF"), anthill_info("None selected"),
      exit("exit"), open("open"), save("save"), start("start"), step("step"),
      previous("previous"), next("next"), simulation(nullptr), timer_val(0), 
      start_state(b_start), timeout_value(750), timer_disconnect(false)
    {
    set_title("Tchanz");
    set_border_width(5);

    add(H_box);
    H_box.pack_start(V_box, Gtk::PACK_SHRINK);
    H_box.pack_start(canvas_box);

    canvas_box.pack_start(canvas);

    V_box.pack_start(general_frame,false,false);
    V_box.pack_start(info_frame,false,false);
    V_box.pack_start(anthill_info_frame,false,false);

    general_frame.add(navbar);

    navbar.pack_start(exit);
    exit.set_size_request(0,60);
    navbar.pack_start(open);
    open.set_size_request(0,60);
    navbar.pack_start(save);
    save.set_size_request(0,60);
    navbar.pack_start(start);
    start.set_size_request(0,60);
    navbar.pack_start(step);
    step.set_size_request(0,60);
    
    info_frame.add(nbF_info);

    anthill_info_frame.add(anthill_info_box);

    anthill_info_box.pack_start(previous);
    anthill_info_box.pack_start(next);
    anthill_info_box.pack_start(anthill_info);

    exit.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_exit));
    open.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_open));
    save.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_save));
    start.signal_clicked().connect(sigc::mem_fun(*this, 
                                                 &Gui::on_button_clicked_start));
    step.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_step));
    next.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked_next));
    previous.signal_clicked().connect(sigc::mem_fun(*this, 
                                                    &Gui::on_button_clicked_previous));

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

void Gui::display_next_hill(bool reverse = false){
    std::string info = this->simulation->get_next_anthill_info(reverse);
    this->anthill_info.set_text(info);
}

void Gui::reset_anthill_info(){
    std::string info = this->simulation->get_next_anthill_info(0,1);
    this->anthill_info.set_text(info);
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
        cr->translate((width - height) / (2 * scale) -0.5 , -0.5);
    }
    else {
        cr->translate(-0.5, (height - width) / (2 * scale) -0.5 );
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
    cout << st_quit << endl;
    hide();
}

void Gui::on_button_clicked_open() {

    Gtk::FileChooserDialog dialog("Please choose a file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    int result = dialog.run();

    switch (result) {
        case (Gtk::RESPONSE_OK): {
            std::string filename = dialog.get_filename();
            this->simulation->clear();
            this->simulation->read_configfile(filename);
            this->reset_anthill_info();
            this->timer_val = 0;
            this->canvas.queue_draw();
            break;
        }
        case (Gtk::RESPONSE_CANCEL): {
            break;
        }
        default: {
            break;
        }
    }
}

void Gui::on_button_clicked_save() {

    Gtk::FileChooserDialog dialog("Please choose a file",
                                  Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Save", Gtk::RESPONSE_OK);

    int result = dialog.run();

    switch (result) {
        case (Gtk::RESPONSE_OK): {
            std::string filename = dialog.get_filename();
            this->simulation->write_configfile(filename);
            break;
        }
        case (Gtk::RESPONSE_CANCEL): {
            break;
        }
        default: {
            break;
        }
    }
}

void Gui::on_button_clicked_start() {
	if(start_state == b_start){
        Glib::signal_timeout().connect(sigc::mem_fun(*this, &Gui::on_timeout),
                                       timeout_value );
        timer_disconnect = false;
        timer_val++;
        start_state = b_stop;
        this->start.set_label("Stop");
	}
	else{
		timer_val--;
        timer_disconnect = true;
		start_state = b_start;
		this->start.set_label("Start");
	}
}

void Gui::on_button_clicked_step() {
	if(start_state == b_start){
        timer_disconnect = false;
        timer_disconnect = true;
        timer_val++;
        std::cout << "This is simulation update number : " << timer_val << std::endl;
	}    
}

void Gui::on_button_clicked_next() {
    display_next_hill();
    this->canvas.queue_draw();
}

void Gui::on_button_clicked_previous() {
    display_next_hill(true);
    this->canvas.queue_draw();
}

bool Gui::on_key_press_event(GdkEventKey * key_event){
    if(key_event->type == GDK_KEY_PRESS){
        switch(gdk_keyval_to_unicode(key_event->keyval)){
            case 'q':
                on_button_clicked_exit();
                break;
            case 's':
                on_button_clicked_start();
                break;
            case '1':
                on_button_clicked_step();
                break;
            case 'n':
                on_button_clicked_next();
                break;
            case 'p':
                on_button_clicked_previous();
                break;
            default:
                break;
        }
    }
    return Gtk::Window::on_key_press_event(key_event);
}

bool Gui::on_timeout(){
    if(timer_disconnect){
        timer_disconnect = false;
        return false;
    }

    std::cout << "This is simulation update number : " << timer_val << std::endl;
    ++timer_val;
    
    // A call to make a single update of the simulation is expected here
    
    // Then a call to refresh the visualization (if any) would be done here
    this->canvas.queue_draw();

    return true; 
}
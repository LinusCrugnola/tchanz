#ifndef GUIGRAPHIC_H
#define GUIGRAPHIC_H

#include <gtkmm.h>
#include <string>

#include "simulation.h"

enum button_state {b_start, b_stop};

class Gui;

class Canvas : public Gtk::DrawingArea {
public:
    Canvas(Gui* parent);
    virtual ~Canvas();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    Gui* parent;
};

class Gui : public Gtk::Window {
public:
    Gui();
    virtual ~Gui();
    void draw_simulation_state();
    unsigned get_dimension();
    void set_simulation(Simulation* simulation);
    void update_nbF();

protected:
    bool on_key_press_event(GdkEventKey* key_event);
    void on_button_clicked_exit();
    void on_button_clicked_open();
    void on_button_clicked_save();
    void on_button_clicked_start();
    void on_button_clicked_step();
    void on_button_clicked_next();
    void on_button_clicked_previous();

    Canvas canvas;

    Gtk::Box H_box;
    Gtk::Box V_box, canvas_box, navbar, anthill_info_box;
    Gtk::Frame general_frame, info_frame, anthill_info_frame;
    Gtk::Label nbF_info, anthill_info;
    Gtk::Button exit, open, save, start, step,
        previous, next;

private:
    Simulation* simulation;
    void display_next_hill(bool reverse);
    void reset_anthill_info();
    bool on_timeout();
    unsigned val;
    button_state state;
    const int timeout_value;
    bool disconnect;
};

#endif

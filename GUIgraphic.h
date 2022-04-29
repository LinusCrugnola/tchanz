/******************************************************************************!
* @file     GUIgraphic.h
* @author   Léo Brückl <leo.bruckl@epfl.ch>             
*           Linus Crugnola <linus.crugnola@epfl.ch>     
* @version  1.0
* @date     29.04.2022
*******************************************************************************/
 
#ifndef GUIGRAPHIC_H
#define GUIGRAPHIC_H

#include <gtkmm.h>
#include <string>

#include "simulation.h"

/**
 * @brief parameter type of button state
 */
enum button_state {b_start, b_stop};

/* Forward declaration of Gui Class */
class Gui;

/**
 * @class Canvas
 * 
 * @brief Area where the Simulation is drawn
 */
class Canvas : public Gtk::DrawingArea {
public:
    /**
     * @brief Construct a new Canvas object
     * 
     * @param parent pointer on the parent window
     */
    Canvas(Gui* parent);

    /**
     * @brief Destroy the Canvas object
     */
    virtual ~Canvas();

protected:
    /**
     * @brief Draw the current state of the simulation
     * 
     * @param cr pointer on cairo
     * @return true if no errors
     */
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    /**
     * @brief pointer on the parent window to update parameters
     */
    Gui* parent;
};

/**
 * @class Graphical UI class
 * 
 * @details contains a Navbar on the left and a Canvas on the right side where the Simulation 
 * is drawn on
 */
class Gui : public Gtk::Window {
public:
    /**
     * @brief Construct the Gui
     */
    Gui();

    /**
     * @brief Destroy the Gui object
     */
    virtual ~Gui();

    /**
     * @brief Draw the current state of the simulaion
     */
    void draw_simulation_state();

    /**
     * @brief Get the dimension of the simulation to initialize the window
     * 
     * @return unsigned dimension
     */
    unsigned get_dimension();

    /**
     * @brief Set the simulation object in Gui
     * 
     * @param simulation pointer on a simulation object
     */
    void set_simulation(Simulation* simulation);

    /**
     * @brief display the current amount of food in the food info frame
     */
    void update_nbF();

protected:
    /**
     * @brief handle the keyboard inputs
     * 
     * @param key_event 
     * @return true if no errors
     */
    bool on_key_press_event(GdkEventKey* key_event);

    /**
     * @brief "exit" button event: quit the program
     */
    void on_button_clicked_exit();

    /**
     * @brief "open" button event: read a new configfile and initialize the simulation
     */
    void on_button_clicked_open();

    /**
     * @brief "save" button event: store the current simulation state in a file
     */
    void on_button_clicked_save();

    /**
     * @brief "start" button event: start the simulation
     * 
     * @remark currently only starts a timer in the terminal
     */
    void on_button_clicked_start();

    /**
     * @brief "step" button event: executes one step of the simulation
     * 
     * @remark currently does one timer step in the terminal
     */
    void on_button_clicked_step();

    /**
     * @brief "next" button event, displays info of next hill and highlights it
     */
    void on_button_clicked_next();

    /**
     * @brief "previous" button event: displays info of previous hill and 
     * highlights it
     */
    void on_button_clicked_previous();

    /**
     * @brief canvas object
     */
    Canvas canvas;

    /**
     * @brief Elements of Navbar
     */
    Gtk::Box H_box;
    Gtk::Box V_box, canvas_box, navbar, anthill_info_box;
    Gtk::Frame general_frame, info_frame, anthill_info_frame;
    Gtk::Label nbF_info, anthill_info;
    Gtk::Button exit, open, save, start, step,
                previous, next;

private:
    /**
     * @brief pointer on the simulation that gui runs
     */
    Simulation* simulation;

    /**
     * @brief display the information of the next anthill
     * 
     * @param reverse if true, display the previous hill
     */
    void display_next_hill(bool reverse);

    /**
     * @brief reset the anthill info frame
     * 
     * @remark displays "None selected"
     */
    void reset_anthill_info();

    /**
     * @brief action on timeout of timer
     * 
     * @return true if the timer counted up
     */
    bool on_timeout();

    /**
     * @brief timer value
     */
    unsigned timer_val;

    /**
     * @brief state of the start button
     * 
     * @remark can be start or stop
     */
    button_state start_state;

    /**
     * @brief defines the timer tick in ms
     */
    const int timeout_value;

    /**
     * @brief indicates if timer is running
     */
    bool timer_disconnect;
};

#endif

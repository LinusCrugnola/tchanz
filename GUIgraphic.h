#ifndef GUIGRAPHIC_H
#define GUIGRAPHIC_H

#include <gtkmm.h>

class Canvas : public Gtk::DrawingArea
{
	public:
		Canvas();
		virtual ~Canvas();
	
	protected:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

class Gui : public Gtk::Window
{
	public:
		Gui();
		virtual ~Gui();
	
	protected:
		
		void on_button_clicked_exit();
		void on_button_clicked_open();
		void on_button_clicked_save();
		void on_button_clicked_start();
		void on_button_clicked_step();
		
		Canvas canvas;
		
		Gtk::Box H_box;
		Gtk::Box V_box, canvas_box, navbar, anthill_info_box;
		Gtk::Frame general_frame, info_frame, anthill_info_frame;
		Gtk::Label nbF_info;
		Gtk::Button exit, open, save, start, step,
					previous, next;
									
};


#endif

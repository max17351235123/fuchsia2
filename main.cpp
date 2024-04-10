#include <gtkmm.h>


#include "MyButton.h"
    int main(int argc, char *argv[])
    {
// Create the application.
        auto app =
                Gtk::Application::create(argc, argv,
                                         "something.more");
// Generate the widow and configure it by setting a size and creating a border.
        Gtk::Window window;
        window.set_default_size(300, 100);
        window.set_border_width(10);
// This will prevent the window from being resized.
        window.set_resizable(false);
// Create 9 stock buttons with different labels that specify the packing
// configuration set below.
        MyButton button11("Button 11 -- PACK_EXPAND_PADDING");
        MyButton button12("Button 12 -- PACK_EXPAND_WIDGET");
        MyButton button13("Button 13 -- EXPAND");
        MyButton button21("Button 21 -- EXPAND");
        MyButton button22("Button 22 -- PACK_EXPAND_PADDING");
        MyButton button23("Button 23 -- PACK_EXPAND_WIDGET");
        MyButton button31("Button 31 -- PACK_EXPAND_WIDGET");
        MyButton button32("Button 32 -- EXPAND");
        MyButton button33("Button 33 -- PACK_EXPAND_PADDING");
// Below each of the three button packings use the same three packing
// algorithms in different order to give some intuition of their
// effects in the rendered window.
// Create one box and pack three buttons into the box.
// This is performed with pack_start, there are other similar methods.
        Gtk::Box hbox1;
        hbox1.pack_start(button11, Gtk::PACK_EXPAND_PADDING, 5);
        hbox1.pack_start(button12,Gtk::PACK_EXPAND_WIDGET, 5);
        hbox1.pack_start(button13,Gtk::EXPAND, 5);
        Gtk::Box hbox2;
        //CS205: Spr 2023 Lab Document Version 7.0 (compiled March 31, 2024) 116
        hbox2.pack_start(button21, Gtk::EXPAND, 5);
        hbox2.pack_start(button22,Gtk::PACK_EXPAND_PADDING, 5);
        hbox2.pack_start(button23,Gtk::PACK_EXPAND_WIDGET, 5);
        Gtk::Box hbox3;
        hbox3.pack_start(button31, Gtk::PACK_EXPAND_WIDGET, 5);
        hbox3.pack_start(button32,Gtk::EXPAND, 5);
        hbox3.pack_start(button33,Gtk::PACK_EXPAND_PADDING, 5);
// This creates a VBox and then packs in the Boxs created above.
        Gtk::VBox vbox;
        vbox.pack_start(hbox1);
        vbox.pack_start(hbox2);
        vbox.pack_start(hbox3);
// The VBox object is then packed into the window.
        window.add(vbox);
// This call will for all children hanging off the window to
// show themselves.
        window.show_all_children();
// Finally this launces the program window.
        return app->run(window);
    }


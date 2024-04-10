#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <iostream>
class MyButton : public Gtk::Button
{
public:
    MyButton();
    MyButton(Glib::ustring s);
    virtual ~MyButton();
protected:
//Signal handlers:
    void on_button_clicked();
//Child widgets:
    Glib::ustring button_label;
};
<<<<<<< HEAD
=======


#ifndef FUCHSIA2_MYBUTTON_H
#define FUCHSIA2_MYBUTTON_H

#endif //FUCHSIA2_MYBUTTON_H
>>>>>>> origin/main

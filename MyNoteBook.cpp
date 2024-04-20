#include <iostream>
#include "MyNoteBook.h"

// The default constructor that initializes some primary window widgets.
MyNoteBook::MyNoteBook()
    : m_VBox     (Gtk::ORIENTATION_VERTICAL),
      button_quit("Quit")
{
    // configure the main window
    set_title("My Note Book Example");
    set_border_width(10);
    set_default_size(400, 200);

    // configure the notebook
    m_Notebook.set_border_width(10);

    //Add the Notebook, with the Quit button underneath.
    m_VBox.pack_start(m_Notebook);

    m_VBox.pack_start(button_box, Gtk::PACK_SHRINK);
    button_box.pack_start(button_quit, Gtk::PACK_SHRINK);

    // Add signal handler to the Quit Button.
    button_quit.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::on_button_quit) );

    // Add the notebook pages.
    initialize_tab_1();
    initialize_tab_2();
    initialize_tab_3();

    // Connect the page switch signal handler to the notebook.
    m_Notebook.signal_switch_page().connect(
            sigc::mem_fun(*this, &MyNoteBook::on_notebook_switch_page) );

    // Add the primary container to the Window, and endure everything is shown.
    add(m_VBox);
    show_all_children();
}

// Initializes the Welcome Screen by setting label, packing it, and adding to notebook.
void MyNoteBook::initialize_tab_1() {
    m_Label1.set_text("Welcome to the Curses Example.");
    tab_box_1.pack_start(m_Label1);
    m_Notebook.append_page(tab_box_1, "Welcome Screen");
}

// Increments the value object, extracts the value and display it.
void MyNoteBook::increment_value() {
    value++;

    // initialize label value
    Glib::ustring str = std::to_string(value.get());
    value_label.set_text(str);
}

// Decrements the value object, extracts the value and display it.
void MyNoteBook::decrement_value() {
    value--;

    // initialize label value
    Glib::ustring str = std::to_string(value.get());
    value_label.set_text(str);
}

// Resets the value object, extracts the value and display it.
void MyNoteBook::reset_value() {
    value = 0;

    // initialize label value
    Glib::ustring str = std::to_string(value.get());
    value_label.set_text(str);
}

// Initializes the Value Screen label/buttons, packing it, and adding to notebook.
void MyNoteBook::initialize_tab_2() {

    // Configure the label font
    auto context = value_label.get_pango_context();
    auto font     = context->get_font_description();
    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_ULTRABOLD);
    font.set_size  (24 * PANGO_SCALE);
    context->set_font_description(font);

    // initialize label value
    Glib::ustring str = std::to_string(value.get());
    value_label.set_text(str);

    // set button labels
    incr_button.set_label("Increment");
    decr_button.set_label("Decrement");
    reset_button.set_label("Reset");

    // pack the buttons
    value_manipulation_buttons.pack_start(incr_button);
    value_manipulation_buttons.pack_start(decr_button);
    value_manipulation_buttons.pack_start(reset_button);

    // connect signal handlers to buttons
    incr_button.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::increment_value) );
    decr_button.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::decrement_value) );
    reset_button.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::reset_value) );

    // pack widgets
    tab_box_2.pack_start(value_label);
    tab_box_2.pack_start(value_manipulation_buttons);
    m_Notebook.append_page(tab_box_2, "Counter Screen");
}

// connect the button press to the displayBuffer action and display
void MyNoteBook::move_north() {
    displayBuffer.move_up();
    render_display();
}

// connect the button press to the displayBuffer action and display
void MyNoteBook::move_south() {
    displayBuffer.move_down();
    render_display();
}

// connect the button press to the displayBuffer action and display
void MyNoteBook::move_east() {
    displayBuffer.move_right();
    render_display();
}

// connect the button press to the displayBuffer action and display
void MyNoteBook::move_west() {
    displayBuffer.move_left();
    render_display();
}

void MyNoteBook::render_display() {

    // reload the buffer in the data class
    displayBuffer.load_buffer();

    // initialized display string
    display_string = "";

    // copy buffer into display string
    for (int row = 0; row < displayBuffer.max_rows(); row++) {
        for (int col = 0; col < displayBuffer   .max_cols(); col++) {
            display_string += displayBuffer.buffer_value(row, col);
        }
        display_string += "\n";
    }

    // copy display string to the label
    display_label.set_text(display_string);
}

// Initializes the Display Screen label/buttons, packing it, and adding to notebook.
void MyNoteBook::initialize_tab_3() {

    // Configure the label font
    auto context = display_label.get_pango_context();
    auto font     = context->get_font_description();
    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_ULTRABOLD);
    font.set_size(24 * PANGO_SCALE);
    context->set_font_description(font);

    render_display();

    // set button labels
    north_button.set_label("North");
    south_button.set_label("South");
    east_button.set_label("East");
    west_button.set_label("West");

    // pack the buttons
    display_manipulation_buttons.pack_start(north_button);
    display_manipulation_buttons.pack_start(south_button);
    display_manipulation_buttons.pack_start(east_button);
    display_manipulation_buttons.pack_start(west_button);

    // connect signal handlers to buttons
    north_button.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::move_north) );
    south_button.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::move_south) );
    east_button.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::move_east) );
    west_button.signal_clicked().connect(
            sigc::mem_fun(*this, &MyNoteBook::move_west) );

    // pack widgets
    tab_box_3.pack_start(display_label);
    tab_box_3.pack_start(display_manipulation_buttons);
    m_Notebook.append_page(tab_box_3, "Map Screen");
}

// destructor
MyNoteBook::~MyNoteBook()
{
}

// signal handler that will quit the program
void MyNoteBook::on_button_quit()
{
    set_visible(false);
}

// signal handler that will be called each time a tab is switched
void MyNoteBook::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
    std::cout << "Switched to tab with index " << page_num << std::endl;
}
#include <gtkmm.h>

int main(int argc, char *argv[]) {
// Create the application.
    auto app =
            Gtk::Application::create(argc, argv, "edu.lafayette.fuchsia2");
// Generate a generic window.
    Gtk::Window window;
// Set the widow size
    window.set_default_size(300, 100);
    return app->run(window);
}
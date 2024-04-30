#include <gtkmm.h>
#include "Database.h"
#include "UserCredentials.h"
#include "Napspot.h"
#include "MyWindow.h"


Database db("napspots.sqlite", "../database");
UserCredentials uc;

Napspot ns("10000");

int main(int argc, char *argv[]) {


    /*
    std::vector<std::string> attribute{"warm"};
    std::vector<std::string> attribute2{"chilly"};
    std::vector<std::string> attribute3{"quiet"};
    std::vector<std::string> attribute4{"noisy"};
    std::vector<std::string> attribute5{"bright"};
    std::vector<std::string> attribute6{"dark"};
    std::vector<std::string> attribute7{"dark", "quiet"};

    ns.clear_napspots();
    ns.add_napspot("cabin", attribute);
    ns.add_napspot("mariana trench", attribute2);
    ns.add_napspot("japan", attribute3);
    ns.add_napspot("himalayas", attribute4);
    ns.add_napspot("garden", attribute5);
    ns.add_napspot("cottage", attribute6);
    ns.add_napspot("lezhis room", attribute7);
    */


    auto app = Gtk::Application::create(argc, argv, "org.example.DatabaseWindow");

    MyWindow window;
    return app->run(window);

}
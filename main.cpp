#include <gtkmm.h>
#include "ButtonWindow.h"
#include "Database.h"
#include "UserCredentials.h"
#include "Napspot.h"
#include "MyWindow.h"
#include <vector>
#include "ReservationWindow.h"

Database db("napspots.sqlite", "../database");
UserCredentials uc;
Napspot ns("1");

int main(int argc, char *argv[]) {

    std::vector<std::string> attribute{"warm"};
    std::vector<std::string> attribute2{"chilly"};
    std::vector<std::string> attribute3{"quiet"};
    std::vector<std::string> attribute4{"noisy"};
    std::vector<std::string> attribute5{"bright"};
    std::vector<std::string> attribute6{"dark"};
    std::vector<std::string> attribute7{"dark", "quiet"};

    ns.clear_napspots();
    ns.add_napspot("quad6", attribute);
    ns.add_napspot("quad3", attribute2);
    ns.add_napspot("quad1", attribute3);
    ns.add_napspot("quad2", attribute4);
    ns.add_napspot("quad4", attribute5);
    ns.add_napspot("qua5", attribute6);
    ns.add_napspot("lezhis room", attribute7);

    ns.add_reservation("1", "5:00");
    ns.add_review("1", "this nap spot rocks", 5);

    std::vector<std::string> output = db.query_all("attributes", "attribute", "napspot_id", "1");

    for (int i = 0; i < output.size(); i++) {
        std::cout << "attribute " << i << " = " << output[i] << std::endl;
    }

    auto app = Gtk::Application::create(argc, argv, "org.example.DatabaseWindow");

    MyWindow window;
    return app->run(window);

    }

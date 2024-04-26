#include <gtkmm.h>
#include <iostream>
#include "Database.h"
#include <sqlite3.h>
#include <vector>
#include "MyWindow.h"
#include <gtkmm/window.h>
#include "Napspot.h"
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>


using namespace std;

Database db("napspots.sqlite", "../database");
UserCredentials uc;
Napspot ns("1");

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <sqlite3.h>
#include <glibmm/value.h>



    class DatabaseWindow : public Gtk::Window {
    public:
        DatabaseWindow(const Glib::ustring& dbPath, const Glib::ustring& tableName)
                : m_dbPath(dbPath), m_tableName(tableName) {
            set_title("Database Window");
            set_default_size(400, 200);

            m_refTreeModel = Gtk::ListStore::create(m_columns);
            m_treeView.set_model(m_refTreeModel);
            m_treeView.append_column("ID", m_columns.m_col_id);
            m_treeView.append_column("Name", m_columns.m_col_name);
            m_treeView.append_column("Attributes", m_columns.m_col_attributes);

            Gtk::TreeViewColumn* buttonColumn = Gtk::manage(new Gtk::TreeViewColumn("Action"));
            Gtk::CellRendererToggle* buttonRenderer = Gtk::manage(new Gtk::CellRendererToggle());
            buttonColumn->pack_start(*buttonRenderer);
            buttonColumn->set_cell_data_func(*buttonRenderer, sigc::mem_fun(*this, &DatabaseWindow::onSetCellData));
            m_treeView.append_column(*buttonColumn);

            m_scrolledWindow.add(m_treeView);
            add(m_scrolledWindow);

            loadDataFromDatabase();

            show_all_children();

    }

private:
    void loadDataFromDatabase() {
        sqlite3* db;
        int rc = sqlite3_open(m_dbPath.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        std::string query = "SELECT * FROM " + m_tableName;
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

            std::vector<std::string> attributes = ns.get_attributes(std::to_string(id));

            Glib::ustring attributeText;
            for (size_t i = 0; i < attributes.size(); ++i) {
                attributeText += attributes[i];
                if (i < attributes.size() - 1) {
                    attributeText += ", ";
                }
            }

            Gtk::TreeModel::Row row = *(m_refTreeModel->append());
            row[m_columns.m_col_id] = id;
            row[m_columns.m_col_name] = name;
            row[m_columns.m_col_attributes] = attributeText;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

        void onSetCellData(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter) {
            Gtk::CellRendererToggle* toggleRenderer = dynamic_cast<Gtk::CellRendererToggle*>(renderer);
            if (toggleRenderer) {
                toggleRenderer->set_active(false);
                toggleRenderer->signal_toggled().connect([this, iter](const Glib::ustring& path) {
                    onButtonToggled(iter);
                });
            }
        }

        void onButtonToggled(const Gtk::TreeModel::iterator& iter) {
            if (iter) {
                Gtk::TreeModel::Row row = *iter;
                int id = row[m_columns.m_col_id];
                // Add functionality for reservation button here
                std::cout << "Button toggled for ID: " << id << std::endl;
            }
        }

        class ModelColumns : public Gtk::TreeModel::ColumnRecord {
        public:
            ModelColumns() {
                add(m_col_id);
                add(m_col_name);
                add(m_col_attributes);
            }

            Gtk::TreeModelColumn<int> m_col_id;
            Gtk::TreeModelColumn<Glib::ustring> m_col_name;
            Gtk::TreeModelColumn<Glib::ustring> m_col_attributes;
        };

        Glib::ustring m_dbPath;
        Glib::ustring m_tableName;
        ModelColumns m_columns;
        Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
        Gtk::TreeView m_treeView;
        Gtk::ScrolledWindow m_scrolledWindow;
    };

class ButtonWindow : public Gtk::Window {
public:
    ButtonWindow() {
        set_title("Choose an Attribute");
        set_default_size(400, 200);

        // Create a grid for the buttons
        auto grid = Gtk::make_managed<Gtk::Grid>();
        add(*grid);

        // Create the buttons
        auto warmButton = Gtk::make_managed<Gtk::Button>("Warm");
        auto chillyButton = Gtk::make_managed<Gtk::Button>("Chilly");
        auto quietButton = Gtk::make_managed<Gtk::Button>("Quiet");
        auto noisyButton = Gtk::make_managed<Gtk::Button>("Noisy");
        auto darkButton = Gtk::make_managed<Gtk::Button>("Dark");
        auto brightButton = Gtk::make_managed<Gtk::Button>("Bright");

        //Connect buttons to open new window
        warmButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "napspots"));
        chillyButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "napspots"));
        quietButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "napspots"));
        noisyButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "napspots"));
        darkButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "napspots"));
        brightButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "napspots"));

        // Add the buttons to the grid
        grid->attach(*warmButton, 0, 0, 1, 1);
        grid->attach(*chillyButton, 2, 0, 1, 1);
        grid->attach(*quietButton, 0, 1, 1, 1);
        grid->attach(*noisyButton, 2, 1, 1, 1);
        grid->attach(*darkButton, 0, 2, 1, 1);
        grid->attach(*brightButton, 2, 2, 1, 1);

        grid->set_column_homogeneous(true);
        grid->set_row_homogeneous(true);

        // Show all widgets
        show_all_children();
    }
    void on_button_clicked(const std::string& dbPath, const std::string& tableName) {
        auto* dbWindow = new DatabaseWindow(dbPath, tableName);
        dbWindow->show();
    }
};


int main(int argc, char *argv[]) {


    //vector<string> empty {};
    vector<string> attribute {"sunny", "noisy"};
    //vector<string> attribute2 {"dark", "quiet"};
    //ns.add_napspot("quad", );

    ns.clear_napspots();
    ns.add_napspot("quad", attribute);
    ns.add_reservation("1","5:00");
    ns.add_review("1", "this nap spot rocks", 5);


    //ns.add_napspot("quad1", attribute);
    //ns.add_napspot("quad2", attribute);
    //ns.add_napspot("quad3", attribute);

    vector<string> output = db.query_all("attributes", "attribute", "napspot_id", "1");

    for (int i = 0; i < output.size(); i++) {
        cout << "attribute " << i << " = " << output[i] << endl;
    }

    auto app = Gtk::Application::create(argc, argv, "org.example.DatabaseWindow");

    // DatabaseWindow window("../database/napspots.sqlite", "napspots");
    ButtonWindow window;
    return app->run(window);

    //test code to run usrnme pswd GUI
    /*
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MyWindow window;
    return app->run(window);
    */


}






#include "DatabaseWindow.h"
#include <iostream>
#include "Database.h"
#include "UserCredentials.h"
#include <sigc++/connection.h>


extern Database db;
extern UserCredentials uc;
extern Napspot ns;

DatabaseWindow::DatabaseWindow(const Glib::ustring& dbPath, const Glib::ustring& tableName)
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

void DatabaseWindow::loadDataFromDatabase() {
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
sigc::connection toggleConnection;

void DatabaseWindow::onSetCellData(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter) {
    Gtk::CellRendererToggle* toggleRenderer = dynamic_cast<Gtk::CellRendererToggle*>(renderer);
    if (toggleRenderer) {
        // Disconnect existing signal connection
        toggleConnection.disconnect();

        toggleRenderer->set_active(false);
        // Connect the signal and store the connection object
        toggleConnection = toggleRenderer->signal_toggled().connect([this, iter, renderer](const Glib::ustring& path) {
            onButtonToggled(iter, renderer); // Pass renderer as a parameter
        });
    }
}

void DatabaseWindow::onButtonToggled(const Gtk::TreeModel::iterator& iter, Gtk::CellRenderer* renderer) {
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        int id = row[m_columns.m_col_id];
        if (!ns.add_reservation(to_string(id), "3:00")) {
            Gtk::MessageDialog dialog(*this, "There is already a reservation at this time!", false,
                                      Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
            dialog.run();
        } else {
            Gtk::MessageDialog dialog(*this, "Reservation made. Hope you're feeling eepy!", false,
                                      Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
            dialog.run();
            Gtk::CellRendererToggle* toggleRenderer = dynamic_cast<Gtk::CellRendererToggle*>(renderer);
            if (toggleRenderer) {
                toggleRenderer->set_active(false);
            }
        }
    }
}

DatabaseWindow::ModelColumns::ModelColumns() {
    add(m_col_id);
    add(m_col_name);
    add(m_col_attributes);
}
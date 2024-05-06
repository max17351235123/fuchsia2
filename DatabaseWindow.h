#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <gtkmm.h>
#include <sqlite3.h>
#include <vector>
#include "Napspot.h"
#include "ReservationWindow.h"

class DatabaseWindow : public Gtk::Window {
public:
    /**
     * Constructs window that displays data from database
     * @param dbPath: path to database (ex: ../napspots.sqlite)
     * @param tableName name of table being displayed in window (in this case the napspots table)
     */
    DatabaseWindow(const Glib::ustring& dbPath, const Glib::ustring& tableName);
private:
    /**
     * Loads data from the database into the TreeView
     */
    void loadDataFromDatabase();
    /**
     * Method for setting up button in each row of data displayed and giving it functionality
     * @param renderer Passes the buttonrenderer object declared in the constructor for setting up a button w/ each row displayed
     * @param iter Used to bind onButtonToggled method to a button being clicked
     */
    void onSetCellData(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
    /**
     * Creates an instance of the ReservationWindow class when clicked
     * @param iter passed to get id of specific row user clicked on
     * @param renderer passed to make sure to toggle the button off after it's clicked
     */
    void onButtonToggled(const Gtk::TreeModel::iterator& iter, Gtk::CellRenderer* renderer);

    /**
     * Private class for modelling the format of the napspot display window
     */
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns();

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

#endif // DATABASEWINDOW_H
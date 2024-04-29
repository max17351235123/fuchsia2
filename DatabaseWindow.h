#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <gtkmm.h>
#include <sqlite3.h>
#include <vector>
#include "Napspot.h"

class DatabaseWindow : public Gtk::Window {
public:
    DatabaseWindow(const Glib::ustring& dbPath, const Glib::ustring& tableName);

private:
    void loadDataFromDatabase();
    void onSetCellData(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
    void onButtonToggled(const Gtk::TreeModel::iterator& iter, Gtk::CellRenderer* renderer);

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
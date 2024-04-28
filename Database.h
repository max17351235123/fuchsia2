#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>

#ifndef FUCHSIA2_DATABASE_H
#define FUCHSIA2_DATABASE_H

using namespace std;

class Database {

public:

    char *ErrMsg;
    sqlite3 *curr_db = nullptr;
    static Database* database;
    string result;
    vector<string> result_vector;
    Database(const string& dbname, const string& dblocation);
    ~Database();
    void open();
    void close();

    static Database* get_db(const string& dbname, const string& dblocation);
    sqlite3* get_curr() const;
    string query(const string& table, const string& output_column, const string& search_column, const string& search);
    int id_query(const string& table, const string& id_column);
    bool add_row(const string& table, const vector<string> &columns, const vector<string>& values);
    bool log_to_csv(const string& table, const string& filename) const;
    bool remove_row(const string& table, const string &id);
    bool clear_table(const string& table);
    vector<string> query_all(const string& table, const string& output_column, const string& search_column, const string& search);
    int double_query(const string& table, const string& con1_column, const string& con1_val, const string& con2_column, const string& con2_val);
    vector<string> get_data(const string& table, const string& id);
    bool subtable(const string& table, const string& subtable, const vector<string>& table_columns, const vector<string>& ids);
    string get_location();
    string get_name();

private:
    string dbname;
    string dblocation;
};

#endif //FUCHSIA2_DATABASE_H

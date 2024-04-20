#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>

#ifndef FUCHSIA2_DATABASE_H
#define FUCHSIA2_DATABASE_H

using namespace std;

class Database {

public:

    int retCode;
    char *zErrMsg;
    sqlite3 *curr_db = nullptr;
    static Database* database;
    string result;
    Database(const string& dbname, const string& dblocation);
    ~Database();
    void open();
    void close();

    static Database* get_db(const string& dbname, const string& dblocation);
    sqlite3* get_curr() const;
    string query(const string& table, const string& column, const string& value, const string& search); //find a value based on the primary key
    bool add_row(sqlite3* db, const string& table, const vector<string> &columns, const vector<string>& values);
    bool log_to_csv(sqlite3* db, const string& table, const string& filename);

        private:
    string dbname;
    string dblocation;


};

#endif //FUCHSIA2_DATABASE_H

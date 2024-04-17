#include "Database.h"
#include <utility>
#include <fstream>
using namespace std;

Database* Database::database = nullptr;

Database::Database(const string& dbname, const string& dblocation) {
    this->dbname = dbname;
    this->dblocation = dblocation;
    open(); //open the database
}
Database::~Database() {
    sqlite3_close(curr_db);
}
Database* Database::get_db(const string& dbname, const string& dblocation) {
    if (database != nullptr) {
        return database;
    }
    database = new Database(dbname, dblocation);
    return database;
}






void Database::open() {
    string full_name = dblocation + "/" + dbname; //find the path based on location and filename

    int rc = sqlite3_open(full_name.c_str(), &curr_db); //open  the database
    if (rc) { //if it doesn't work send error message
        cerr << "Database does not open -- "
             << sqlite3_errmsg(curr_db) << endl;
        cerr << " File -- " << full_name << endl;
        exit(0);
    } else {
        cerr << "Opened database successfully" << endl; //if it works send confirmation message
    }
}

sqlite3* Database::get_curr() const {
    return curr_db;
}
/*
string query(const string& table, string id) {

    string target = table + "_id";
    string sql = "SELECT id FROM" + target + "WHERE id = " + id + ';';
    const char* C = sql.c_str()



}
*/

void Database::close() {
    if (curr_db) {
        sqlite3_close(curr_db);
        curr_db = nullptr;
    }
}

bool Database::add_row(sqlite3* db, const string& table, const vector<string> &columns, const vector<string>& values) {

    string sql = "INSERT INTO " + table + " (";
    for (int i = 0; i < columns.size(); i++) {
        sql += columns[i];
        if (i != columns.size() - 1) {
            sql += ", ";
        }
    }
    sql += ") VALUES (";
    for (int i = 0; i < values.size(); i++) {
        sql += "'" + values[i] + "'";
        if (i != values.size() - 1) {
            sql += ", ";
        }
    }
    sql += ")";

    cout << sql << endl;

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Row added successfully." << std::endl;
        string csvfile = dblocation + "/csv/" + table + ".csv";
        log_to_csv(db, table, csvfile);
    }
    return true;
}






bool Database::log_to_csv(sqlite3* db, const string& table, const string& filename) {
    ofstream csv_file(filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open CSV file: " << filename << std::endl;
        return false;
    }

    std::string sql = "SELECT * FROM " + table;

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    int num_columns = sqlite3_column_count(stmt);
    for (int i = 0; i < num_columns; ++i) {
        csv_file << sqlite3_column_name(stmt, i);
        if (i < num_columns - 1) {
            csv_file << ",";
        }
    }
    csv_file << std::endl;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < num_columns; ++i) {
            const unsigned char *column_value = sqlite3_column_text(stmt, i);
            csv_file << column_value;
            if (i < num_columns - 1) {
                csv_file << ",";
            }
        }
        csv_file << std::endl;
    }

    sqlite3_finalize(stmt);
    csv_file.close();
    return true;
}

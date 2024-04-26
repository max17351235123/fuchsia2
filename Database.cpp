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

string Database::get_location() {
    return dblocation;
}

string Database::get_name() {
    return dbname;
}

static int cb_one(void *data, int argc, char **argv, char **azColName) {
    auto* db = static_cast<Database*>(data);
    if (argc > 0 && argv[0] != nullptr) {
        db->result = argv[0];
    }
    return 0;
}

static int cb_all(void *data, int argc, char **argv, char **azColName) {
    auto* db = static_cast<Database*>(data);
    for(int i = 0; i < argc; i++) {
        db->result_vector.emplace_back(argv[i]);
    }
    return 0;
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
    }
}

sqlite3* Database::get_curr() const {
    return curr_db;
}

string Database::query(const string& table, const string& output_column, const string& search_column, const string& search) {
    // Construct the SQL query string
    result.clear();
    string sql = "SELECT " + output_column + " FROM " + table + " WHERE " + search_column + " = '" + search + "';";

    char *errMsg = nullptr;


    int rc = sqlite3_exec(get_curr(), sql.c_str(), cb_one, this, &errMsg);
    //int rc = sqlite3_exec(get_curr(), sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return "";
    } else {
        if (result.empty()) {
            cerr << "search not found" << endl;
            return "";
        }
        else {
            return result;
        }
    }
}

int Database::id_query(const string& table, const string& id_column) {
    result.clear();
    string sql = "SELECT MAX(" + id_column + ") FROM " + table + ";";
    char *errMsg = nullptr;

    int rc = sqlite3_exec(get_curr(), sql.c_str(), cb_one, this, &errMsg);


    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 0;
    } else {
        if (result.empty()) {
            cerr << "search not found" << endl;
            return 0;
        }
        else {
            return stoi(result);
        }
    }
}


void Database::close() {
    if (curr_db) {
        sqlite3_close(curr_db);
        curr_db = nullptr;
    }
}

bool Database::add_row(const string& table, const vector<string> &columns, const vector<string>& values) {

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

    char *errMsg = nullptr;
    int rc = sqlite3_exec(get_curr(), sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    } else {
        string csvfile = dblocation + "/csv/" + table + ".csv";
        log_to_csv(table, csvfile);
    }
    return true;
}

bool Database::log_to_csv(const string& table, const string& filename) const {
    ofstream csv_file(filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open CSV file: " << filename << std::endl;
        return false;
    }

    std::string sql = "SELECT * FROM " + table;

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(get_curr(), sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(get_curr()) << std::endl;
        return false;
    }

    int num_columns = sqlite3_column_count(stmt);

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

bool Database::remove_row(const string &table, const string &id) {
    string table2 = table;
    string idname = table2.erase(table.size() - 1);
    string sql = "DELETE FROM " + table + " WHERE " + idname + "_id" + " = '" + id + "';";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(get_curr(), sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        string csvfile = dblocation + "/csv/" + table + ".csv";
        log_to_csv(table, csvfile);
    }
    return true;
}

bool Database::clear_table(const string& table) {
    string sql = "DELETE FROM " + table;
    char *errMsg = nullptr;
    int rc = sqlite3_exec(get_curr(), sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    } else {
        string csvfile = dblocation + "/csv/" + table + ".csv";
        log_to_csv(table, csvfile);
        return true;
    }
}

vector<string> Database::query_all(const string& table, const string& output_column, const string& search_column, const string& search) {
    // Construct the SQL query string
    result_vector.clear();
    string sql = "SELECT " + output_column + " FROM " + table + " WHERE " + search_column + " = '" + search + "';";

    char *errMsg = nullptr;

    int rc = sqlite3_exec(get_curr(), sql.c_str(), cb_all, this, &errMsg);
    //int rc = sqlite3_exec(get_curr(), sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return {};
    } else {
        if (result_vector.empty()) {
            cerr << "search not found > query_all()" << endl;
            return {};
        }
        else {
            return result_vector;
        }
    }
}

int Database::double_query(const string& table, const string& con1_column, const string& con1_val, const string& con2_column, const string& con2_val){
    result.clear();
    string sql = "SELECT COUNT(*) AS result "
                 "FROM " + table + " WHERE " +
                 con1_column + " = " + con1_val
                 + " AND " + con2_column + " = " + "'" + con2_val + "'" + ";";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(get_curr(), sql.c_str(), cb_one, this, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 0;
    } else {
        if (result.empty()) {
            cerr << "search not found" << endl;
            return 0;
        }
        else {
            return stoi(result);
        }
    }
}




//string sql = "SELECT COUNT(*) AS reservation_count FROM reservations WHERE user_id = " + user_id +
//                 " AND DATE(time, 'unixepoch') = DATE(" + res_time + ", 'start of day')";



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

    /**
     * returns a reference to the database
     * @param dbname
     * @param dblocation
     * @return reference to the database
     */
    static Database* get_db(const string& dbname, const string& dblocation);
    /**
     * gets current database
     * @return current database
     */
    sqlite3* get_curr() const;
    /**
     * querys a value based on a given other value
     * @param table table to query
     * @param output_column the column containing the output value
     * @param search_column the column contaiing the input value
     * @param search the input value
     * @return value in the same row as the given value
     */
    string query(const string& table, const string& output_column, const string& search_column, const string& search);
    /**
     * returns the highest id in a table
     * @param table the table being searched
     * @param id_column the name of the id column
     * @return highest id
     */
    int id_query(const string& table, const string& id_column);
    /**
     * adds a row to a table
     * @param table table to add the row too
     * @param columns the columns in the table
     * @param values the values to add to each column
     * @return true if successful, false if not
     */
    bool add_row(const string& table, const vector<string> &columns, const vector<string>& values);
    /**
     * updates the a csv file based on the contents of a table
     * @param table name of the table
     * @param filename name of the filename
     * @return true if successful, false if not
     */
    bool log_to_csv(const string& table, const string& filename) const;
    /**
     * removes a row in a table
     * @param table table you are removing from
     * @param id id of the row you are removing
     * @return true if successful, false if not
     */
    bool remove_row(const string& table, const string &id);
    /**
     * clears a table
     * @param table table to clear
     * @return true if successful, false if not
     */
    bool clear_table(const string& table);
    /**
     * queries an entire table
     * @param table the table you are querying
     * @param output_column the column containing the output value
     * @param search_column the column containing the search column
     * @param search the value searched for
     * @return returns a vector of all values that match the search
     */
    vector<string> query_all(const string& table, const string& output_column, const string& search_column, const string& search);
    /**
     * queries a value based on 2 conditions
     * @param table the table queried
     * @param con1_column condition 1 column
     * @param con1_val condition 1 value
     * @param con2_column condition 2 column
     * @param con2_val condition 2 value
     * @return the value that fufills the 2 conditions
     */
    int double_query(const string& table, const string& con1_column, const string& con1_val, const string& con2_column, const string& con2_val);
    /**
     * gets the data from a row
     * @param table table searched
     * @param id id of the row
     * @return all of the columns' values in a row as a vector
     */
    vector<string> get_data(const string& table, const string& id);
    /**
     * creates a smaller table based on ids
     * @param table name of the original table
     * @param subtable name of the new subtable
     * @param table_columns the columns of the original table
     * @param ids the ids to add into the subtable
     * @return true if sucessful, false if not
     */
    bool subtable(const string& table, const string& subtable, const vector<string>& table_columns, const vector<string>& ids);
    /**
     * @return the name of the database location
     */
    string get_location();
    /**
     * @return the name of the database
     */
    string get_name();

private:
    string dbname;
    string dblocation;
};

#endif //FUCHSIA2_DATABASE_H

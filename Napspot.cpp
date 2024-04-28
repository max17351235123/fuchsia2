#include "Napspot.h"
#include "Database.h"
#include <iostream>
#include <vector>
#include <sqlite3.h>

Napspot::Napspot(const string& user_id) {
    db = Database::get_db("napspots.sqlite", "../database");
    this->user_id = user_id;
}

Napspot::~Napspot() {
    db->close();
}

bool Napspot::add_napspot(const string& name, const vector<string>& attributes) {
    //increment the id by 1
    int napspot_id = db->id_query("napspots", "napspot_id") + 1;

    //add the row
    vector<string> input = {to_string(napspot_id), name};
    if (!db->add_row("napspots", napspot_column, input)) {
        return false;
    }

    //add the attributes
    for (const auto & attribute : attributes) {
        add_attribute(to_string(napspot_id), attribute);
    }
    return true;
}

bool Napspot::add_attribute(const string& napspot_id, const string& attribute) {

    //increment the id
    int attribute_id = db->id_query("attributes", "attribute_id") + 1;
    vector<string> input = {to_string(attribute_id), napspot_id, attribute};

    //add to attribute table
    db->add_row("attributes", attribute_column, input);
    return true;
}

bool Napspot::add_review(const string& napspot_id, const string& txt, const int rating) {
    int review_id = db->id_query("reviews", "review_id") + 1;

    //"review_id", "user_id", "napspot_id", "txt", "rating"};
    vector<string> input = {to_string(review_id), user_id, napspot_id, txt, to_string(rating)};
    db->add_row("reviews", review_column, input);
    return true;
}

//need to change to only focus on day instead of exact time
bool Napspot::add_reservation(const string& napspot_id, const string& time) {
    int reservation_id = db->id_query("reservations", "reservation_id") + 1;

    //{"reservation_id", "user_id", "napspot_id", "time"};
    vector<string> input = {to_string(reservation_id), user_id, napspot_id, time};
    if (db->double_query("reservations", "user_id", user_id, "start_time", time) > 0) {
        cerr << "can only make 1 reservation per day" << endl;
        return false;
    }

    db->add_row("reservations", reservation_column, input);
    return true;
}

bool Napspot::remove_napspot(const string& name) {
    //find the id based on name
    string napspot_id = db->query("napspots", "napspot_id", "name", name);

    //remove the row
    db->remove_row("napspots", napspot_id);
    remove_dependants(napspot_id, "attributes");
    remove_dependants(napspot_id, "reservations");
    remove_dependants(napspot_id, "reviews");
    return true;
}

//remove every review/attribute/reservation associated with given napspot id
bool Napspot::remove_dependants(const string& napspot_id, const string& table) {

    string table2 = table;
    string idname = table2.erase(table.size() - 1);

    //loop through the attributes that have the napspot id
    while (!db->query(table, idname, "napspot_id", napspot_id).empty()) {
        string output = db->query(table, idname, "napspot_id", napspot_id);

        //remove it
        db->remove_row(table, output);
    }
    return true;
}

bool Napspot::clear_napspots() {
    db->clear_table("napspots");
    db->clear_table("attributes");
    db->clear_table("reservations");
    db->clear_table("reviews");
    return true;
}

vector<string> Napspot::get_attributes(const string& napspot_id) {
    return db->query_all("attributes","attribute", "napspot_id",napspot_id);
}

vector<string> Napspot::filter_by_attribute(const string& attribute) {
    db->clear_table("filtered_napspots");

    //find all the napspots with X attribute
    vector<string> output = db->query_all("attributes", "napspot_id", "attribute", attribute);
    db->subtable("napspots","filtered_napspots",napspot_column,output);
    return output;
}




/*
 * click filter by attribute
 * return x napspot_ids that have that attribute
 * display those x napspots
 */
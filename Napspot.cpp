#include "Napspot.h"
#include "Database.h"
#include <iostream>
#include <vector>
#include <sqlite3.h>

Napspot::Napspot() {
    db = Database::get_db("napspots.sqlite", "../database");
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
    vector<string> input = {napspot_id, to_string(attribute_id), attribute};

    //add to attribute table
    db->add_row("attributes", attribute_column, input);
    return true;
}

bool Napspot::remove_napspot(const string& name) {
    //find the id based on name
    string napspot_id = db->query("napspots", "napspot_id", "name", name);

    //remove the row
    db->remove_row("napspots", napspot_id);
    remove_attribute(napspot_id);
    return true;
}

//remove every attribute associated with given napspot id
bool Napspot::remove_attribute(const string& napspot_id) {


    //loop through the attributes that have the napspot id
    while (!db->query("attributes", "attribute_id", "napspot_id", napspot_id).empty()) {
        string output = db->query("attributes", "attribute_id", "napspot_id", napspot_id);

        //remove it
        db->remove_row("attributes", output);
    }
    return true;
}

bool Napspot::clear_napspots() {
    db->clear_table("napspots");
    db->clear_table("attributes");
    return true;
}

/*
vector<string> Napspot::get_attribute(const string& name) {
    return null;
}
 */


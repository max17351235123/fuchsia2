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
    int napspot_id = db->id_query("napspots", "napspot_id") + 1;

    vector<string> input = {to_string(napspot_id), name};
    db->add_row("napspots", napspot_column, input);
    for (const auto & attribute : attributes) {
        add_attribute(to_string(napspot_id), attribute);
    }
    return true;
}

bool Napspot::add_attribute(const string& napspot_id, const string& attribute) {
    int attribute_id = db->id_query("attributes", "attribute_id") + 1;
    vector<string> input = {napspot_id, to_string(attribute_id), attribute};

    db->add_row("attributes", attribute_column, input);
    return true;
}

bool Napspot::remove_napspot(const string& name) {
    string napspot_id = db->query("napspots", "napspot_id", "name", name);
    db->remove_row("napspots", napspot_id);
    return true;
}

vector<string> Napspot::get_attribute(const string& name) {
    return null;
}
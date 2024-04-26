//
// Created by max votaw on 4/23/24.
//

#ifndef FUCHSIA2_NAPSPOT_H
#define FUCHSIA2_NAPSPOT_H
#include <string>
#include <unordered_map>
#include "Database.h"

class Napspot {


public:

    vector<string> napspot_column = {"napspot_id", "name"};
    vector<string> attribute_column = {"attribute_id, ""napspot_id", "attribute"};
    vector<string> review_column = {"review_id", "user_id", "napspot_id", "txt", "rating"};
    vector<string> reservation_column = {"reservation_id", "user_id", "napspot_id", "start_time"};
    string user_id;

    Napspot(const string& user_id);
    ~Napspot();
    bool add_napspot(const string& name, const vector<string>& attributes);
    bool add_attribute(const string& napspot_id, const string& attribute);
    bool remove_napspot(const string &name);
    bool remove_dependants(const string& napspot_id, const string& table);
    bool clear_napspots();
    vector<string> get_attributes(const string& napspot_id);
    bool add_review(const string& napspot_id, const string& txt, int rating);
    bool add_reservation(const string& napspot_id, const string& time);


private:
    Database *db;

};


#endif //FUCHSIA2_NAPSPOT_H


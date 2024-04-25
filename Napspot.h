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
    vector<string> attribute_column = {"napspot_id, ""attribute_id", "attribute"};


    Napspot();
    ~Napspot();
    bool add_napspot(const string& name, const vector<string>& attributes);
    bool add_attribute(const string& napspot_id, const string& attribute);
    bool remove_napspot(const string &name);
    bool remove_attribute(const string& napspot_id);
    bool clear_napspots();

private:
    Database *db;

};


#endif //FUCHSIA2_NAPSPOT_H


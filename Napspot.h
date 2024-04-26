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

    /**
     * default constructor for the napspot class, every user will automatically generate a napspot object once they login
     *
     * @param user_id the user id of the user currently logged in
     */
    explicit Napspot(const string& user_id);

    /**
     * default deconstructor for the napspot class
     */
    ~Napspot();

    /**
     * adds a nap spot
     *
     * @param name name of the nap spot
     * @param attributes the attributes of the napspot
     * @return true if successful, false if not
     */
    bool add_napspot(const string& name, const vector<string>& attributes);

    /**
     * adds an attribute
     *
     * @param napspot_id napspot_id to associate the attribute to
     * @param attribute the attribute being added
     * @return true if succesful, false if not
     */
    bool add_attribute(const string& napspot_id, const string& attribute);

    /**
     * removes a nap spot
     *
     * @param name name of napspot being removed
     * @return true if succesful, false if not
     */
    /**
     * removes entries from the table that is associated with the given napspot
     *
     * @param napspot_id napspot to search for dependants of
     * @param table table to remove from
     * @return true if successful, false if not
     */
    bool remove_dependants(const string& napspot_id, const string& table);

    /**
     * clears all napspots, and consequently all depedants of those napspots
     *
     * @return true if successful, false if not
     */
    bool clear_napspots();

    /**
     * returns the attributes of a given nap spot
     *
     * @param napspot_id napspot to search for attributes of
     * @return vector of all attributes
     */
    vector<string> get_attributes(const string& napspot_id);

    /**
     * adds a review to a napspot
     *
     * @param napspot_id napspot being reviewed
     * @param txt the text of the review
     * @param rating the rating given to the napspot
     * @return true if successful, false if not
     */

    bool add_review(const string& napspot_id, const string& txt, int rating);
    /**
     * adds a reservation to a napspot
     *
     * @param napspot_id napspot being reviewed
     * @param start_time the start time of the reservation
     * @return true if successful, false if not
     */
    bool add_reservation(const string& napspot_id, const string& start_time);

    /**
     * returns all napspots that have the given attribute
     *
     * @param attribute the attribute being filtered for
     * @return a vector of all the napspots with that attribute
     */
    vector<string> filter_by_attribute(const string& attribute);
    bool remove_napspot(const string& name);
private:

    Database *db;

};


#endif //FUCHSIA2_NAPSPOT_H


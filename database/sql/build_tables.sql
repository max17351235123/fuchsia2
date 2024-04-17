CREATE TABLE locations (
      location_id     INT NOT NULL UNIQUE,
      name            TEXT NOT NULL,
      attribute       TEXT NOT NULL,
      reservation     BOOL NOT NULL,
      PRIMARY KEY (location_id)
);

CREATE TABLE reviews (
      review_id         INT NOT NULL UNIQUE,
      user_id     TEXT NOT NULL,
      location_id TEXT NOT NULL,
      txt        TEXT NOT NULL,
      mother     TEXT NOT NULL,
      PRIMARY KEY (review_id),
      FOREIGN KEY (user_id) REFERENCES users(id),
      FOREIGN KEY (location_id) REFERENCES locations(id)
);

CREATE TABLE users (
      user_id    INT NOT NULL UNIQUE,
      username   TEXT NOT NULL,
      password   TEXT NOT NULL,
      PRIMARY KEY (user_id)
);


.separator ","
.mode csv
.import "csv/locations.csv" locations
.import "csv/users.csv"  users
.import "csv/reviews.csv" reviews
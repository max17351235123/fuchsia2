CREATE TABLE napspots (
      napspot_id     INT NOT NULL UNIQUE,
      name            TEXT NOT NULL UNIQUE,
      PRIMARY KEY (napspot_id)
);

CREATE TABLE attributes (
    attribute_id INT NOT NULL UNIQUE,
    napspot_id INT NOT NULL,
    attribute TEXT NOT NULL,
    PRIMARY KEY (attribute_id),
    FOREIGN KEY (napspot_id) REFERENCES napspots(napspot_id) ON DELETE CASCADE
);


CREATE TABLE reviews (
      review_id    INT NOT NULL UNIQUE,
      user_id     TEXT NOT NULL,
      napspot_id TEXT NOT NULL,
      txt        TEXT NOT NULL,
      PRIMARY KEY (review_id),
      FOREIGN KEY (user_id) REFERENCES users(user_id),
      FOREIGN KEY (napspot_id) REFERENCES napspots(napspot_id)
);

CREATE TABLE reservations (
    reservation_id INT NOT NULL UNIQUE,
    user_id TEXT NOT NULL,
    napspot_id TEXT NOT NULL,
    time TEXT NOT NULL,
    PRIMARY KEY (reservation_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (napspot_id) REFERENCES napspots(napspot_id)
);

CREATE TABLE users (
      user_id    INT NOT NULL UNIQUE,
      username   TEXT NOT NULL,
      password   TEXT NOT NULL,
      PRIMARY KEY (user_id)
);


.separator ","
.mode csv
.import "csv/napspots.csv" napspots
.import "csv/users.csv"  users
.import "csv/reviews.csv" reviews
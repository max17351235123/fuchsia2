
opendbms:
	sqlite3 ./napspots.sqlite

drop:
	sqlite3 ./napspots.sqlite < ./sql/drop_tables.sql

build:
	sqlite3 ./napspots.sqlite < ./sql/build_tables.sql

clean:
	rm -f napspots.sqlite
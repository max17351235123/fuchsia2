cmake_minimum_required(VERSION 3.22)
project(fuchsia2)

set(CMAKE_CXX_STANDARD 14)


find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})


add_executable(fuchsia2
        main.cpp
        Database.h
        Database.cpp
        MyWindow.cpp
        UserCredentials.cpp
        Napspot.cpp
        ButtonWindow.cpp
        ButtonWindow.h
        DatabaseWindow.cpp
        DatabaseWindow.h
        DatabaseWindow.h
        ReservationWindow.cpp
        ReservationWindow.h
)

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(fuchsia2 sqlite3)
target_link_libraries(fuchsia2 ${GTKMM_LIBRARIES})

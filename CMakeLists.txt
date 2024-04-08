cmake_minimum_required(VERSION 3.27)
project(fuchsia2)

set(CMAKE_CXX_STANDARD 14)



# setting up the pkgconfig tool obtain the gtkmm4 locations
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})


add_executable(fuchsia2
        main.cpp)


include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(fuchsia2 sqlite3)
target_link_libraries(fuchsia2 ${GTKMM_LIBRARIES})

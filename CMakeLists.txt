cmake_minimum_required(VERSION 3.22)
project(fuchsia2)

set(CMAKE_CXX_STANDARD 14)

add_executable(fuchsia2
        main.cpp)


include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(fuchsia2 sqlite3)


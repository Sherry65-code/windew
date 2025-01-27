cmake_minimum_required(VERSION 3.5)

project(windew)

include_directories(include)

add_library(windew STATIC src/windew_unix.cpp src/windew_win64.cpp include/windew/windew.hpp)

set(TESTING YES)

# For testing only
if(TESTING)
    add_executable(windew_test src/windew_test.cpp)
    target_link_libraries(windew_test windew)
endif()
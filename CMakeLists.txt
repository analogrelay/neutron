cmake_minimum_required(VERSION 3.2)

set(NEUTRON_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

project(neutron
        VERSION 0.0.1
        LANGUAGES CXX)

include(cmake/vars.cmake)
include(cmake/macros.cmake)
include(vendor/cef/cef.cmake)

include_directories(.)
include_directories(vendor/jsoncpp)
include_directories(vendor/cef/${NEUTRON_BUILD_PLATFORM})

add_subdirectory(vendor/cef)
add_subdirectory(src)

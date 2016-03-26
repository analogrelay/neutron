cmake_minimum_required(VERSION 3.2)

include_directories(../../include)

set(SOURCES
    neutron.cpp)

add_executable(neutron ${SOURCES})

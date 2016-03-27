cmake_minimum_required(VERSION 3.2)

set(HEADERS
    neutron_app.h
    neutron_app_definition.h
    neutron_broker.h
    neutron_handler.h
    neutron_server.h
    pal.h)
if(OS_WINDOWS)
    list(APPEND HEADERS windows_neutron_server.h)
endif()
source_group("Header Files" FILES ${HEADERS})

set(JSON_CPP
    ../../vendor/jsoncpp/jsoncpp.cpp
    ../../vendor/jsoncpp/json/json.h
    ../../vendor/jsoncpp/json/json-forwards.h)
source_group("Vendor\\JsonCpp" FILES ${JSON_CPP})

set(SOURCES
    neutron.cpp
    neutron_app.cpp
    neutron_broker.cpp
    neutron_server.cpp
    neutron_handler.cpp
    neutron_app_definition.cpp)

if(OS_WINDOWS)
    list(APPEND SOURCES windows_neutron_server.cpp)
endif()

source_group("Source Files" FILES ${SOURCES})

if(OS_WINDOWS)
    add_executable(neutron WIN32 ${SOURCES} ${HEADERS} ${JSON_CPP})
    add_dependencies(neutron libcef_dll_wrapper)
    target_link_libraries(neutron libcef_lib libcef_dll_wrapper)

    # Copy required files to output
    COPY_FILES(neutron "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
    COPY_FILES(neutron "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
endif()


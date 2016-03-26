cmake_minimum_required(VERSION 3.2)

set(SOURCES
    neutron.cpp
    neutron_app.cpp
    neutron_handler.cpp)

if(OS_WINDOWS)
    add_executable(neutron WIN32 ${SOURCES})
    add_dependencies(neutron libcef_dll_wrapper)
    target_link_libraries(neutron libcef_lib libcef_dll_wrapper)

    # Copy required files to output
    COPY_FILES(neutron "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
    COPY_FILES(neutron "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
endif()


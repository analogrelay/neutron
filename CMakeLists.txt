cmake_minimum_required(VERSION 3.2)

set(NEUTRON_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

project(neutron
        VERSION 0.0.1
        LANGUAGES CXX)

include(cmake/macros.cmake)
include(cmake/vars.cmake)
include(vendor/cef/cef.cmake)

if(OS_WINDOWS)
    # Standard definitions
    # -DWIN32 -D_WIN32 -D_WINDOWS           = Windows platform
    # -DUNICODE -D_UNICODE                  = Unicode build
    # -DWINVER=0x0602 -D_WIN32_WINNT=0x602  = Targeting Windows 8
    # -DNOMINMAX                            = Use the standard's templated min/max
    # -DWIN32_LEAN_AND_MEAN                 = Exclude less common API declarations
    # -D_HAS_EXCEPTIONS=0                   = Disable exceptions
    add_definitions(-DWIN32 -D_WIN32 -D_WINDOWS -DUNICODE -D_UNICODE -DWINVER=0x0602
                    -D_WIN32_WINNT=0x602 -DNOMINMAX -DWIN32_LEAN_AND_MEAN -D_HAS_EXCEPTIONS=0)
endif()

include_directories(.)
include_directories(vendor/jsoncpp)
include_directories(vendor/cef/${NEUTRON_BUILD_PLATFORM})

add_subdirectory(vendor/cef)
add_subdirectory(src)

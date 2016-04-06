set(NEUTRON_BUILD_ARCH "x64")

# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(OS_MACOSX 1)
    set(OS_POSIX 1)
    set(NEUTRON_BUILD_OS "darwin")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OS_LINUX 1)
    set(OS_POSIX 1)
    set(NEUTRON_BUILD_OS "linux")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(OS_WINDOWS 1)
    set(NEUTRON_BUILD_OS "win")
    set(CMAKE_GENERATOR_PLATFORM "Win64")
endif()

set(NEUTRON_BUILD_PLATFORM "${NEUTRON_BUILD_OS}-${NEUTRON_BUILD_ARCH}")
set(NEUTRON_BUILD_VENDOR_CEF "${NEUTRON_REPO_ROOT}/vendor/cef/${NEUTRON_BUILD_PLATFORM}")

set(CMAKE_CXX_STANDARD 11)

if(OS_WINDOWS)
    # Standard definitions
    # -DWIN32 -D_WIN32 -D_WINDOWS           = Windows platform
    # -DUNICODE -D_UNICODE                  = Unicode build
    # -DWINVER=0x0602 -D_WIN32_WINNT=0x602  = Targeting Windows 8
    # -DNOMINMAX                            = Use the standard's templated min/max
    # -DWIN32_LEAN_AND_MEAN                 = Exclude less common API declarations
    # -D_HAS_EXCEPTIONS=0                   = Disable exceptions
    add_definitions(-DOS_WINDOWS -DWIN32 -D_WIN32 -D_WINDOWS -DUNICODE -D_UNICODE -DWINVER=0x0602
                    -D_WIN32_WINNT=0x602 -DNOMINMAX -DWIN32_LEAN_AND_MEAN -D_HAS_EXCEPTIONS=0)
elseif(OS_MACOSX)
    add_definitions(-DOS_MACOSX)
elseif(OS_LINUX)
    add_definitions(-DOS_LINUX)
endif()

if(OS_POSIX)
    add_definitions(-DOS_POSIX)
endif()


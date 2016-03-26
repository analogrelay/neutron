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

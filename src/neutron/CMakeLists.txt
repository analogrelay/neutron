cmake_minimum_required(VERSION 3.2)

set(HEADERS
    neutron_app.h
    neutron_app_definition.h
    neutron_broker.h
    neutron_handler.h
    neutron_server.h
    pal.h)
if(OS_WINDOWS)
    list(APPEND HEADERS windows/windows_neutron_server.h)
endif()
source_group("Header Files" FILES ${HEADERS})

set(JSON_CPP
    ../../vendor/jsoncpp/jsoncpp.cpp
    ../../vendor/jsoncpp/json/json.h
    ../../vendor/jsoncpp/json/json-forwards.h)
source_group("Vendor\\JsonCpp" FILES ${JSON_CPP})

set(SOURCES
    neutron_app.cpp
    neutron_broker.cpp
    neutron_server.cpp
    neutron_handler.cpp
    neutron_app_definition.cpp)

if(OS_WINDOWS)
    list(APPEND SOURCES
         windows/neutron.cpp
         windows/windows_neutron_server.cpp)
elseif(OS_MACOSX)
    list(APPEND SOURCES
         mac/neutron.mm)
    set(HELPER_SOURCES
        mac/process_helper_mac.cpp)
endif()

source_group("Source Files" FILES ${SOURCES})

if(OS_MACOSX)
    set(RESOURCES
        mac/Resources/English.lproj/InfoPlist.strings
        mac/Resources/English.lproj/MainMenu.xib
        mac/Resources/Info.plist
        mac/Resources/cefsimple.icns)
endif()

set(ALL_SOURCES ${SOURCES} ${HEADERS} ${JSON_CPP})

set(CEF_TARGET "neutron")
set(CEF_HELPER_TARGET "neutron_Helper")

if(OS_WINDOWS)
    add_executable(${CEF_TARGET} WIN32 ${ALL_SOURCES})
    target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper)

    # Copy required files to output
    COPY_FILES(${CEF_TARGET} "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
    COPY_FILES(${CEF_TARGET} "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
elseif(OS_MACOSX)
    # Output paths for the app bundles.
    set(CEF_APP "${CEF_TARGET_OUT_DIR}/${CEF_TARGET}.app")
    set(CEF_HELPER_APP "${CEF_TARGET_OUT_DIR}/${CEF_HELPER_TARGET}.app")

    add_executable(${CEF_HELPER_TARGET} MACOSX_BUNDLE ${HELPER_SOURCES})
    target_link_libraries(${CEF_HELPER_TARGET} libcef_lib libcef_dll_wrapper)
    set_target_properties(${CEF_HELPER_TARGET} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/mac/Resources/helper-Info.plist)

    # Fix the framework link in the helper executable.
    FIX_MACOSX_HELPER_FRAMEWORK_LINK(${CEF_HELPER_TARGET} ${CEF_HELPER_APP})

    add_executable(${CEF_TARGET} MACOSX_BUNDLE ${RESOURCES} ${ALL_SOURCES})
    add_dependencies(${CEF_TARGET} ${CEF_HELPER_TARGET})
    target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper)
    set_target_properties(${CEF_TARGET} PROPERTIES
        RESOURCE "${RESOURCES}"
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/mac/Resources/Info.plist)

    # Copy files into the main app bundle.
    add_custom_command(
        TARGET ${CEF_TARGET}
        POST_BUILD
        # Copy the helper app bundle into the Frameworks directory.
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CEF_HELPER_APP}"
                "${CEF_APP}/Contents/Frameworks/${CEF_HELPER_TARGET}.app"
        # Copy the CEF framework into the Frameworks directory.
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CEF_BINARY_DIR}/Chromium Embedded Framework.framework"
                "${CEF_APP}/Contents/Frameworks/Chromium Embedded Framework.framework"
        VERBATIM)

    # Fix the framework link in the main executable.
    FIX_MACOSX_MAIN_FRAMEWORK_LINK(${CEF_TARGET} ${CEF_APP})

    if(NOT ${CMAKE_GENERATOR} STREQUAL "Xcode")
        # Manually process and copy over resource files.
        # The Xcode generator handles this via the set_target_properties RESOURCE directive.
        set(PREFIXES "mac/")  # Remove these prefixes from input file paths.
        COPY_MACOSX_RESOURCES("${RESOURCES}" "${PREFIXES}" "${CEF_TARGET}" "${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_APP}")
    endif()
endif()


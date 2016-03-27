set(NEUTRON_CEF_ROOT "${NEUTRON_REPO_ROOT}/vendor/cef/${NEUTRON_BUILD_PLATFORM}")

if(OS_WINDOWS)
    # Platform-specific compiler/linker flags.
    set(CEF_LIBTYPE                 STATIC)

    # Standard libraries.
    set(CEF_STANDARD_LIBS "comctl32.lib" "rpcrt4.lib" "shlwapi.lib")

    # CEF directory paths.
    set(CEF_RESOURCE_DIR        "${NEUTRON_CEF_ROOT}/Resources")
    set(CEF_BINARY_DIR          "${NEUTRON_CEF_ROOT}/$<CONFIGURATION>")
    set(CEF_BINARY_DIR_DEBUG    "${NEUTRON_CEF_ROOT}/Debug")
    set(CEF_BINARY_DIR_RELEASE  "${NEUTRON_CEF_ROOT}/Release")

    # CEF library paths.
    set(CEF_LIB_DEBUG   "${CEF_BINARY_DIR_DEBUG}/libcef.lib")
    set(CEF_LIB_RELEASE "${CEF_BINARY_DIR_RELEASE}/libcef.lib")

    # List of CEF binary files.
    set(CEF_BINARY_FILES
        d3dcompiler_43.dll
        d3dcompiler_47.dll
        libcef.dll
        libEGL.dll
        libGLESv2.dll
        natives_blob.bin
        snapshot_blob.bin
    )

    if(PROJECT_ARCH STREQUAL "x86")
        # Only used on 32-bit platforms.
        set(CEF_BINARY_FILES
            ${CEF_BINARY_FILES}
            wow_helper.exe
        )
    endif()

    # List of CEF resource files.
    set(CEF_RESOURCE_FILES
        cef.pak
        cef_100_percent.pak
        cef_200_percent.pak
        cef_extensions.pak
        devtools_resources.pak
        icudtl.dat
        locales
    )
elseif(OS_MACOSX)
    # Platform-specific compiler/linker flags.
    set(CEF_LIBTYPE                 SHARED)

    # Standard libraries.
    set(CEF_STANDARD_LIBS "-lpthread" "-framework Cocoa" "-framework AppKit")

    # CEF directory paths.
    set(CEF_BINARY_DIR          "${NEUTRON_CEF_ROOT}/$<CONFIGURATION>")
    set(CEF_BINARY_DIR_DEBUG    "${NEUTRON_CEF_ROOT}/Debug")
    set(CEF_BINARY_DIR_RELEASE  "${NEUTRON_CEF_ROOT}/Release")

    # CEF library paths.
    set(CEF_LIB_DEBUG   "${CEF_BINARY_DIR_DEBUG}/Chromium Embedded Framework.framework/Chromium Embedded Framework")
    set(CEF_LIB_RELEASE "${CEF_BINARY_DIR_RELEASE}/Chromium Embedded Framework.framework/Chromium Embedded Framework")
endif()

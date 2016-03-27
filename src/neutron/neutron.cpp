#include <Windows.h>

#include "neutron_app.h"
#include "include/cef_app.h"
#include "include/cef_sandbox_win.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    // Enable High-DPI support on Windows 7 or newer.
    CefEnableHighDPISupport();

    // Provide CEF with command-line arguments.
    CefMainArgs main_args(hInstance);

    // Create CEF Settings
    CefSettings settings;
    settings.no_sandbox = true;

    // Create App
    CefRefPtr<neutron_app> app(new neutron_app());

    // CEF applications have multiple sub-processes (render, plugin, GPU, etc)
    // that share the same executable. This function checks the command-line and,
    // if this is a sub-process, executes the appropriate logic.
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) {
        // The sub-process has completed so return here.
        return exit_code;
    }

    // Initialize CEF
    CefInitialize(main_args, settings, app, nullptr);

    // Run the message loop
    CefRunMessageLoop();

    // Shutdown
    CefShutdown();
    return 0;
}
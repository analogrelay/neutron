#pragma once

#include "include/cef_app.h"

class neutron_app : public CefApp,
    public CefBrowserProcessHandler {

public:
    neutron_app();

    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
        OVERRIDE {
        return this;
    }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(neutron_app);
};
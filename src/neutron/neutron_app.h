#pragma once

#include "common.h"

#include "include/cef_app.h"

#include "neutron_server.h"
#include "neutron_broker.h"
#include "neutron_app_definition.h"

class neutron_app : public CefApp,
    public CefBrowserProcessHandler,
    public CefRenderProcessHandler {

public:
    neutron_app();

    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
        OVERRIDE {
        return this;
    }

    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()
        OVERRIDE {
        return this;
    }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

    // CefRenderProcessHandler methods
    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) OVERRIDE;

private:
    CefRefPtr<neutron_broker> m_broker;
    CefRefPtr<neutron_app_definition> m_definition;
    CefRefPtr<neutron_server> m_server;

    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(neutron_app);
};

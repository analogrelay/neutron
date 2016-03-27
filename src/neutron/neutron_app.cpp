#include <string>

#include "neutron_app.h"
#include "neutron_handler.h"
#include "neutron_app_definition.h"

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"

neutron_app::neutron_app() : m_broker(new neutron_broker()) {
}

void neutron_app::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    // Information used when creating the native window.
    CefWindowInfo window_info;

#if defined(OS_WIN)
    // On Windows we need to specify certain flags that will be passed to
    // CreateWindowEx().
    window_info.SetAsPopup(NULL, "Neutron Shell");
#endif

    // SimpleHandler implements browser-level callbacks.
    CefRefPtr<neutron_handler> handler(new neutron_handler());

    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;

    CefRefPtr<CefCommandLine> command_line =
        CefCommandLine::GetGlobalCommandLine();

    // Load the app definition
    auto app = command_line->GetSwitchValue("app");
    if (app.empty()) {
        // TODO: App location
        // TODO: Error handling
        exit(1);
    }
    m_definition = neutron_app_definition::load(app);
    if (!m_definition)
    {
        // TODO: Error handling
        exit(2);
    }

    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, handler.get(), m_definition->index(),
        browser_settings, NULL);
}

void neutron_app::OnContextCreated(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context) {

    // Get 'window'
    auto window = context->GetGlobal();

    // Create 'neutron' object
    CefRefPtr<CefV8Accessor> accessor = m_broker;
    auto neutron = CefV8Value::CreateObject(accessor);
    neutron->SetValue("flob", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);

    // Store it
    window->SetValue("neutron", neutron, static_cast<cef_v8_propertyattribute_t>(
        V8_PROPERTY_ATTRIBUTE_READONLY | V8_PROPERTY_ATTRIBUTE_DONTENUM | V8_PROPERTY_ATTRIBUTE_DONTDELETE));
}

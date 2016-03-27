#pragma once

#include "include/cef_v8.h"

class neutron_broker : public CefV8Accessor {
public:
    neutron_broker();

    virtual bool Get(const CefString & name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString & exception) override;
    virtual bool Set(const CefString & name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString & exception) override;

private:
    IMPLEMENT_REFCOUNTING(neutron_broker)
};
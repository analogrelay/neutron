#pragma once

#include "include/cef_base.h"

class neutron_server abstract : public CefBase {
public:
    static CefRefPtr<neutron_server> start(const CefString& working_dir, const CefString& command);
};
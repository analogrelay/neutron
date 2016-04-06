#pragma once

#include "common.h"

class neutron_server : public CefBase {
public:
    static CefRefPtr<neutron_server> start(const CefString& working_dir, const CefString& command);
};

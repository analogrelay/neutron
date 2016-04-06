#pragma once

#include "common.h"

#include "neutron_server.h"

class mac_neutron_server : public neutron_server
{
public:
    static CefRefPtr<mac_neutron_server> start(const CefString& working_dir, const CefString& command);

private:

    IMPLEMENT_REFCOUNTING(mac_neutron_server);
};

#include "neutron_server.h"

#if WIN32
#include "windows_neutron_server.h"
#endif

CefRefPtr<neutron_server> neutron_server::start(const CefString& working_dir, const CefString& command)
{
#if WIN32
    return windows_neutron_server::start(working_dir, command);
#endif
}

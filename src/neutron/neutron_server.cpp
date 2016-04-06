#include "common.h"

#include "neutron_server.h"

#if OS_WINDOWS
#include "windows/windows_neutron_server.h"
#elif OS_MACOSX
#include "mac/mac_neutron_server.h"
#endif

CefRefPtr<neutron_server> neutron_server::start(const CefString& working_dir, const CefString& command)
{
#if WIN32
    return windows_neutron_server::start(working_dir, command);
#else
    return mac_neutron_server::start(working_dir, command);
#endif
}

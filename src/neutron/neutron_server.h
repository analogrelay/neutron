#pragma once

#include "include/cef_base.h"

#if WIN32
class windows_neutron_server: public CefBase
{
public:
    static CefRefPtr<windows_neutron_server> start(const CefString& working_dir, const CefString& command);

private:
    windows_neutron_server(HANDLE job, PROCESS_INFORMATION process) : m_job(job), m_process(process) {}
    HANDLE m_job;
    PROCESS_INFORMATION m_process;

    IMPLEMENT_REFCOUNTING(windows_neutron_server);
};

#endif

class neutron_server : public CefBase {
public:
    static CefRefPtr<neutron_server> start(const CefString& working_dir, const CefString& command);

private:
#if WIN32
    neutron_server(CefRefPtr<windows_neutron_server> impl) : m_impl(impl) {}

    CefRefPtr<windows_neutron_server> m_impl;
#endif

    IMPLEMENT_REFCOUNTING(neutron_server)
};
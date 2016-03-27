#pragma once

#include "include/cef_base.h"

#include "neutron_server.h"

class windows_neutron_server: public neutron_server
{
public:
    static CefRefPtr<windows_neutron_server> start(const CefString& working_dir, const CefString& command);

    void run_thread();

private:
    windows_neutron_server(HANDLE job, PROCESS_INFORMATION process);
    HANDLE m_job;
    HANDLE m_thread;
    PROCESS_INFORMATION m_process;

    IMPLEMENT_REFCOUNTING(windows_neutron_server);
};
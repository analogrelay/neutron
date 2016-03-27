#include <WinSock2.h>

#include "windows_neutron_server.h"

#include "include/cef_app.h"
#include "include/base/cef_bind.h"

DWORD WINAPI NeutronServerThreadProc(LPVOID param) {
    static_cast<windows_neutron_server*>(param)->run_thread();
    return 0;
}

windows_neutron_server::windows_neutron_server(HANDLE job, PROCESS_INFORMATION process) : m_job(job), m_process(process) {
    // Create a thread to manage the connection
    m_thread = CreateThread(nullptr, 0, NeutronServerThreadProc, this, 0, nullptr);
}

void windows_neutron_server::run_thread() {
}

CefRefPtr<windows_neutron_server> windows_neutron_server::start(const CefString& working_dir, const CefString& command)
{
    // TODO: Don't set this in this process, just do it in the child
    // TODO: Allow this to be configured, also pick a free port or named pipe?
    SetEnvironmentVariable(L"NEUTRON_URL", L"neutron+http://localhost:9494");

    // Create a Job Object to hold the process
    auto job = CreateJobObject(nullptr, nullptr);

    std::wstring buf;
    buf.reserve(command.length());
    buf.append(command.c_str());

    STARTUPINFO info;
    ZeroMemory(&info, sizeof(info));
    info.cb = sizeof(info);

    // Create the process
    PROCESS_INFORMATION process;
    ZeroMemory(&process, sizeof(process));
    if (!CreateProcess(
        nullptr,
        const_cast<wchar_t*>(buf.c_str()),
        nullptr,
        nullptr,
        false,
        CREATE_NEW_CONSOLE,
        nullptr,
        working_dir.c_str(),
        &info,
        &process)) {
        return nullptr;
    }

    if (!AssignProcessToJobObject(job, process.hProcess)) {
        TerminateProcess(process.hProcess, 1);
        return nullptr;
    }

    return new windows_neutron_server(job, process);
}

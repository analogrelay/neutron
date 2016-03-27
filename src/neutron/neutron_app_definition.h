#pragma once

#include "include/cef_base.h"

class neutron_app_definition : public CefBase {
public:
    static CefRefPtr<neutron_app_definition> neutron_app_definition::load(const CefString& definition_path);

    CefString index();
    const CefString& base_directory() { return this->m_base_directory; };
    const CefString& server_command() { return this->m_server_command; };

private:
    neutron_app_definition(CefString base_directory, CefString index_path, CefString server_command) :
        m_base_directory(base_directory), m_index_path(index_path), m_server_command(server_command) {}

    CefString m_base_directory;
    CefString m_index_path;
    CefString m_server_command;

    IMPLEMENT_REFCOUNTING(neutron_app_definition);
};
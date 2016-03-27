#include <fstream>
#include <algorithm>

#include "pal.h"
#include "json/json.h"

#include "neutron_app_definition.h"

CefRefPtr<neutron_app_definition> neutron_app_definition::load(const CefString& definition_path) {
    Json::Value root;

    auto path = definition_path.ToString16();
    auto last_dir_end = path.find_last_of(pal::directory_separator);
    if (last_dir_end == std::wstring::npos || last_dir_end == 0)
    {
        return nullptr;
    }
    auto dir_name = path.substr(0, last_dir_end);

    // Load the file, then close it
    {
        std::ifstream file(definition_path.c_str(), std::ifstream::in);

        // Skip byte-order mark
        if (file.peek() == 0xEF) {
            file.ignore(1);
            if (file.peek() == 0xBB) {
                file.ignore(1);
                if (file.peek() == 0xBF) {
                    file.ignore(1);
                }
            }
        }

        file >> root;
    }
    auto index = root.get("index", "index.html").asString();
    auto server = root.get("server", Json::Value::null);

    std::string command;
    if (!server.isNull())
    {
        command = server.get("command", "").asString();
    }

#if WIN32
    std::replace(index.begin(), index.end(), '/', pal::directory_separator_utf8);
#endif

    return new neutron_app_definition(dir_name, index, command);
}

CefString neutron_app_definition::index() {
    std::wstring ret;
    ret.reserve(m_base_directory.length() + m_index_path.length() + 1);
    ret.append(m_base_directory.c_str());
    ret.push_back(pal::directory_separator);
    ret.append(m_index_path.c_str());
    return ret;
}
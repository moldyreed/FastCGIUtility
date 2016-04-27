#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <iostream>
#include <dbus/dbus.h>
#include "json.hpp"

typedef nlohmann::json json;

class NetworkConfig
{
public:
    static std::string result();
};

#endif // NETWORKCONFIG_H

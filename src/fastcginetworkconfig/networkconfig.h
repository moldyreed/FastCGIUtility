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
private:
	static std::string CIDRLongToString(const long mask);
};

#endif // NETWORKCONFIG_H

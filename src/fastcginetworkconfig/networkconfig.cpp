#include "networkconfig.h"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DBUS_NAME "org.freedesktop.NetworkManager"
#define DBUS_PATH "/org/freedesktop/NetworkManager/IP4Config/0"
#define DBUS_IFACE  "org.freedesktop.DBus.Properties"
#define DBUS_METHOD_GET  "GetAll"
#define DBUS_TIMEOUT 5

static const char* dev = "org.freedesktop.NetworkManager.IP4Config";

std::string NetworkConfig::result()
{
	std::unique_ptr<DBusConnection, void (*)(DBusConnection*)> conn(dbus_bus_get(DBUS_BUS_SYSTEM, NULL), dbus_connection_unref);

	if (!conn)
		throw std::runtime_error("Can't get on system bus");

	DBusMessageIter iter, iter_array, iter_dict, iter_prop;
	long mask = 0;
	char* property_ptr;
	char* key_ptr;
	int current_type;
	std::string ip;
	std::string gateway;
	std::unique_ptr<DBusMessage, void (*)(DBusMessage*)> message(dbus_message_new_method_call(DBUS_NAME, DBUS_PATH, DBUS_IFACE, DBUS_METHOD_GET), dbus_message_unref);

	if (!message.get())
		throw std::runtime_error("Can't get on system bus");

	dbus_message_iter_init_append(message.get(), &iter);
	dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &dev);
	std::unique_ptr<DBusMessage, void (*)(DBusMessage*)> reply(dbus_connection_send_with_reply_and_block(conn.get(), message.get(), DBUS_TIMEOUT, NULL), dbus_message_unref);

	if (!dbus_message_iter_init(reply.get(), &iter))
		throw std::runtime_error("networkmanager_get_property dbus_message_iter_init error");

	dbus_message_iter_recurse(&iter, &iter_array);

	while ((current_type = dbus_message_iter_get_arg_type(&iter_array)) != DBUS_TYPE_INVALID)
	{
		if (dbus_message_iter_get_arg_type(&iter_array) == DBUS_TYPE_DICT_ENTRY)
		{
			dbus_message_iter_recurse(&iter_array, &iter_dict);
			dbus_message_iter_get_basic(&iter_dict, &key_ptr);

			if (dbus_message_iter_next(&iter_dict))
			{
				dbus_message_iter_recurse(&iter_dict, &iter_prop);

				if (strcmp(key_ptr, "AddressData") == 0)
				{
					DBusMessageIter _array;
					dbus_message_iter_recurse(&iter_prop, &_array);

					while ((current_type = dbus_message_iter_get_arg_type(&_array)) != DBUS_TYPE_INVALID)
					{
						if (dbus_message_iter_get_arg_type(&_array) == DBUS_TYPE_DICT_ENTRY)
						{
							dbus_message_iter_recurse(&_array, &iter_prop);
							dbus_message_iter_get_basic(&iter_prop, &key_ptr);
							dbus_message_iter_next(&iter_prop);
							dbus_message_iter_recurse(&iter_prop, &iter_prop);

							if (strcmp(key_ptr, "address") == 0)
							{
								if (dbus_message_iter_get_arg_type(&iter_prop) == DBUS_TYPE_STRING)
								{
									dbus_message_iter_get_basic(&iter_prop, &property_ptr);
									ip = property_ptr;
								}
								else
									throw std::runtime_error("[DBUS] address is not a string type");
							}

							if (strcmp(key_ptr, "prefix") == 0)
							{
								if (dbus_message_iter_get_arg_type(&iter_prop) == DBUS_TYPE_UINT32)
								{
									dbus_message_iter_get_basic(&iter_prop, &mask);
								}
								else
									throw std::runtime_error("[DBUS] prefix is not a uint32 type");
							}
						}
						else if (dbus_message_iter_get_arg_type(&_array) == DBUS_TYPE_ARRAY)
						{
							dbus_message_iter_recurse(&_array, &_array);
							continue;
						}

						dbus_message_iter_next(&_array);
					}
				}

				if (strcmp(key_ptr, "Gateway") == 0)
				{
					if (dbus_message_iter_get_arg_type(&iter_prop) == DBUS_TYPE_STRING)
					{
						dbus_message_iter_get_basic(&iter_prop, &property_ptr);
						gateway = property_ptr;
					}
					else
						throw std::runtime_error("[DBUS] address is not a string type");
				}
			}
		}

		dbus_message_iter_next(&iter_array);
	}

	json _json
	{
		{"ip", ip},
		{"netmask", NetworkConfig::CIDRLongToString(mask)},
		{"gateway", gateway}
	};
	return _json.dump(4);
}

std::string NetworkConfig::CIDRLongToString(const long maskbits)
{
	struct in_addr netmask;
	int mask;

	if (maskbits < 1 || maskbits > 30)
		throw std::runtime_error("[NetworkConfig] wrong netmask");

	mask = 0;

	for (int i = 0 ; i < maskbits ; i++)
		mask |= 1 << (31 - i);

	netmask.s_addr = htonl(mask);
	char* res = inet_ntoa(netmask);
	return std::string(res);
}
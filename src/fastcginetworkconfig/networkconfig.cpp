#include "networkconfig.h"

std::string NetworkConfig::result()
{
	json _json{{"u", "1"}, {"dsda", "dasd"}};
	return _json.dump(4);
}

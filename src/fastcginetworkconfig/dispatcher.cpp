#include "dispatcher.h"

#include "networkconfig.h"

std::string Dispatcher::query(const FCGX_Request &req)
{
    // cut REQUEST_URI to ?
    const std::string& requestQuery { FCGX_GetParam("REQUEST_URI", req.envp)};
    const std::string& path{Dispatcher::path(requestQuery)};

    if(path.compare("/config") == 0)
    {
        return NetworkConfig::result();
    }

    return "None";
}

std::string Dispatcher::path(const std::string &requestURI)
{
    size_t queryBeginning = requestURI.find("?");
    return requestURI.substr(0, queryBeginning);
}

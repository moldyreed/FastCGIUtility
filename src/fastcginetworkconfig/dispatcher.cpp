#include "dispatcher.h"

#include <fnmatch.h>

#include "networkconfig.h"

Dispatcher::Dispatcher()
{
	// we can register any pattern like /v1/*/config
	// firstly add /config
	registerPathForFunction("/config", std::bind(&NetworkConfig::result));
	//secondly add pattern /v1/*/config, to get work requests such as /v1/network/config
	registerPathForFunction("/v1/*/config", std::bind(&NetworkConfig::result));
}

std::string Dispatcher::query(const FCGX_Request& req)
{
	// cut REQUEST_URI to ?
	const std::string& requestQuery { FCGX_GetParam("REQUEST_URI", req.envp)};
	const std::string& requestedPath{Dispatcher::path(requestQuery)};

	try
	{
		// iterate over all path and match it
		for (auto& pair : _pathsFunctions)
		{
			const std::string& path = pair.first;

			if (fnmatch(path.c_str(), requestedPath.c_str(), 0) == 0)
				return pair.second();
		}
	}
	catch (std::exception& e)
	{
		return json{{"error", e.what()}} .dump(4);
	}

	return "404";
}

std::set<std::string> Dispatcher::availiblePaths()
{
	std::set<std::string> result;

	for (auto& v : _pathsFunctions)
	{
		result.emplace(v.first);
	}

	return result;
}

std::string Dispatcher::path(const std::string& requestURI)
{
	size_t queryBeginning = requestURI.find("?");
	return requestURI.substr(0, queryBeginning);
}

bool Dispatcher::registerPathForFunction(const std::string& pathPattern, std::function<std::string()> func)
{
	if (pathPattern.empty())
		return false;

	_pathsFunctions.emplace(pathPattern, func);
}

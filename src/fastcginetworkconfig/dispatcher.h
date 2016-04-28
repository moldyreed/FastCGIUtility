#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <functional>
#include <set>
#include <map>
#include <fcgiapp.h>

class Dispatcher
{
public:
	// thread safe singleton
	static Dispatcher& sharedInstance()
	{
		static Dispatcher instance;
		return instance;
	}

	std::string query(const FCGX_Request& req);
	std::set<std::string> availiblePaths();
private:
	Dispatcher();
	virtual ~Dispatcher() {}
	Dispatcher(Dispatcher&) = delete;

	static std::string path(const std::string& requestURI);
	bool registerPathForFunction(const std::string& pathPattern, std::function<std::string()> func);

	std::map<std::string, std::function<std::string()>> _pathsFunctions;

};

#endif // DISPATCHER_H

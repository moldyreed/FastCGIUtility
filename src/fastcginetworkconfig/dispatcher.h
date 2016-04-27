#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <fcgiapp.h>

class Dispatcher
{
public:
    static std::string query(const FCGX_Request& req);
private:
    static std::string path(const std::string& requestURI);

};

#endif // DISPATCHER_H

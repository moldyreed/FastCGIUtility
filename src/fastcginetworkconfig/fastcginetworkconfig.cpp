#include "fastcginetworkconfig.h"

#include <unistd.h>
#include "dispatcher.h"

FastCGINetworkConfig::FastCGINetworkConfig(const int nThreads):
	_nThreads(nThreads)
{
}

void FastCGINetworkConfig::init()
{
    _socketId = FCGX_OpenSocket(SOCKET_PATH, FASTCGI_LIMIT);
    if(_socketId < 0)
        throw std::runtime_error("Can't open socket.");

    for(int i = 0 ; i < _nThreads; i++)
    {
        _threads.push_back(std::thread(&FastCGINetworkConfig::read, this));
    }
}

void FastCGINetworkConfig::read()
{
    int rc;
    FCGX_Request request;
    if(FCGX_InitRequest(&request, _socketId, 0) != 0)
    {
        throw std::runtime_error("Can't init request");
    }

    while(true)
    {
            // not need to lock mutex - function is thread safe
            rc = FCGX_Accept_r(&request);
            if(rc < 0)
               throw std::runtime_error("Can not accept new request\n");

            std::cout << std::this_thread::get_id() << std::endl;

            FCGX_PutS("\r\n", request.out);
            const std::string & result = Dispatcher::query(request);
            FCGX_PutS(result.c_str(), request.out);
            FCGX_PutS("\r\n", request.out);
            FCGX_Finish_r(&request);
    }
}


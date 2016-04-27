#ifndef FASTCGINETWORKCONFIG_H
#define FASTCGINETWORKCONFIG_H

#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <signal.h>
#include <fcgiapp.h>

#define SOCKET_PATH "127.0.0.1:9000"
#define FASTCGI_LIMIT 20

class FastCGINetworkConfig
{
public:
	FastCGINetworkConfig(const int nThreads);
	void init();
    void read();

private:

    std::vector<std::thread> _threads;
    const int               _nThreads;
    int                     _socketId;
    bool                    _run;

};

#endif // FASTCGINETWORKCONFIG_H

#include <iostream>
#include <memory>

// getopt
#include <getopt.h>

// fastcgi C lib
#include <fcgiapp.h>

#include "fastcginetworkconfig.h"

int main(int argc, char* argv[])
{
	try
	{
		if (FCGX_Init() != 0)
			throw std::runtime_error("Can't initilize FastCGI library.");

		int opt;
		int nThreads = 5;

		while ((opt = getopt(argc, argv, "n:")) != -1)
		{
			switch (opt)
			{
				case 'n':
					nThreads = std::atoi(optarg);
					break;
			}
		}

		FastCGINetworkConfig app(nThreads);
		app.init();
		app.read();
		FCGX_Finish();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

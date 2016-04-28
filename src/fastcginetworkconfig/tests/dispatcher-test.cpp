
#include "gtest/gtest.h"

#include <string>
#include <fstream>

#define private public
#include "dispatcher.h"

TEST(dispatcher, path)
{
	{
		const std::string& query = "/v1/config?a=b&b=c";
		EXPECT_EQ("/v1/config", Dispatcher::path(query));
	}
	
	{
		const std::string& query = "/v1/config";
		EXPECT_EQ("/v1/config", Dispatcher::path(query));
	}
}

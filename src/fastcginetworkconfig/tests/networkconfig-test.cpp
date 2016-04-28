
#include "gtest/gtest.h"

#include <string>
#include <fstream>

#define private public
#include "networkconfig.h"

TEST(networkconfig, CIDR)
{
	{
		long mask = 22;
		EXPECT_EQ("255.255.252.0", NetworkConfig::CIDRLongToString(mask));
	}
	{
		long mask = 35;
		EXPECT_THROW(NetworkConfig::CIDRLongToString(mask), std::exception);
	}
}

#include <gtest/gtest.h>
#include "utils.hpp"


TEST (UtilsTests, IpParserTest)
{
    std::vector<std::string> testString{"192","168","0","111"};

    auto ip=ipParser(testString);
    if(ip)
    {
        auto val=ip.value();

        EXPECT_EQ (val[0], 192);
        EXPECT_EQ (val[1], 168);
        EXPECT_EQ (val[2], 0);
        EXPECT_EQ (val[3], 111);

        return;

    }
    FAIL();
}

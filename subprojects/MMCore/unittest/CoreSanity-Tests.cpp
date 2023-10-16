// #define CATCH_CONFIG_MAIN isn't working yet
#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>

#include "MMCore.h"

TEST_CASE("CoreSanityTests/CreateAndDestroyTwice", "CoreSanityTests")
{
    {
        CMMCore c1;
    }
    {
        CMMCore c2;
    }
}

TEST_CASE("CoreSanityTests/CreateTwoAtOnce", "CoreSanityTests")
{
    CMMCore c1;
    CMMCore c2;
}

TEST_CASE("CoreSanityTests/CreateAndReset", "CoreSanityTests")
{
    CMMCore c;
    c.reset();
}


TEST_CASE("CoreSanityTests/getAPIVersionInfo", "CoreSanityTests")
{
    CMMCore c;
    REQUIRE(c.getAPIVersionInfo() == "Device API version 71, Module API version 10");   
}


int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);
    return result;
}

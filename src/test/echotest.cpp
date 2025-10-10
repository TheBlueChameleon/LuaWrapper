#include <iostream>
#include <string>
using namespace std::string_literals;

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

constexpr auto testDir = "./testScripts/";

static int funcPtr(lua_State* L)
{
    return 0;
}

TEST(EchoTest, InvokeRawTest)
{
    auto state = LuaState(testDir + "identity.lua"s);
    lua_State* sPtr = state.expose();
    LuaFunction f = state.getFunction("identity");

    {
        ParameterStack ps = {1};
        ParameterStack result = f.invoke(sPtr, ps);
        std::cout << "got " << result.size() << " return values" << std::endl;
        for (const LuaEntity* x : result)
        {
            std::cout << x->to_string() << std::endl;
        }
    }
    {
        ParameterStack ps = {1};
        ASSERT_THROW(LuaFunction("doesNotExist"s, funcPtr).invoke(sPtr, ps), LuaInvalidArgumentError);

    }

}

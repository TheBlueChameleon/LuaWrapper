#include <iostream>
#include <string>
using namespace std::string_literals;

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

constexpr auto testDir = "./testScripts/";

TEST(StateTest, FooTest)
{
    auto state = LuaState(testDir + "identity.lua"s);
}

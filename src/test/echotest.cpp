#include <iostream>
#include <string>
using namespace std::string_literals;

#include <gtest/gtest.h>

#include <luawrapper.hpp>

#include "commonconversionutil.hpp"

using namespace LuaWrapper;

constexpr auto testDir = "./testScripts/";

TEST(EchoTest, PathologicCallsTest)
{
    auto state = LuaState(testDir + "identity.lua"s);
    lua_State* sPtr = state.expose();

    {
        ParameterStack ps = {1};
        ASSERT_THROW(LuaFunction(""s, funcPtr).invoke(sPtr, ps), LuaInvalidArgumentError);

    }
    {
        ParameterStack ps = {1};
        ASSERT_THROW(LuaFunction("doesNotExist"s, nullptr).invoke(sPtr, ps), LuaInvalidArgumentError);

    }
    {
        ParameterStack ps = {1};
        ASSERT_THROW(LuaFunction("doesNotExist"s, funcPtr).invoke(sPtr, ps), LuaInvalidStateError);

    }
    {
        ASSERT_THROW(state.invoke("multiVariate", ParameterStack()), LuaCallError);

    }
}

TEST(EchoTest, InvokeRawTest)
{
    auto state = LuaState(testDir + "identity.lua"s);
    lua_State* sPtr = state.expose();
    LuaFunction f = state.getFunction("identity");
    {
        ParameterStack ps = {nullptr};
        ParameterStack result = f.invoke(sPtr, ps);

        ASSERT_EQ(result.size(), 1);
        ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Nil);
    }
    {
        ParameterStack ps = {true};
        ParameterStack result = f.invoke(sPtr, ps);

        ASSERT_EQ(result.size(), 1);
        ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Boolean);
        EXPECT_EQ(result.at(0)->asLuaBoolean().getValue(), true);
    }
    {
        ParameterStack ps = {getVoidPtr()};
        ParameterStack result = f.invoke(sPtr, ps);

        ASSERT_EQ(result.size(), 1);
        ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::LightUserData);
        EXPECT_EQ(result.at(0)->asLuaLightUserData().getValue(), funcPtr);
    }
    {
        ParameterStack ps = {1};
        ParameterStack result = f.invoke(sPtr, ps);

        ASSERT_EQ(result.size(), 1);
        ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Number);
        EXPECT_EQ(result.at(0)->asLuaNumber().getValue(), 1);
    }
    {
        ParameterStack ps = {"text"s};
        ParameterStack result = f.invoke(sPtr, ps);

        ASSERT_EQ(result.size(), 1);
        ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::String);
        EXPECT_EQ(result.at(0)->asLuaString().getValue(), "text");
    }
}

TEST(EchoTest, InvokeMultiVariateTest)
{
    auto state = LuaState(testDir + "identity.lua"s);
    {
        ParameterStack result = state.invoke("multiVariate", ParameterStack({1, 2}));
        ASSERT_EQ(result.size(), 2);
        ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Number);
        ASSERT_EQ(result.at(1)->getTypeId(), LuaTypeId::Number);
        EXPECT_EQ(result.at(0)->asLuaNumber().getValue(), -1);
        EXPECT_EQ(result.at(1)->asLuaNumber().getValue(), +3);
    }
}

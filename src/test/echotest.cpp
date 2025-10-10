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

    // nameless function
    ASSERT_THROW(LuaFunction(""s, funcPtr).invoke(sPtr, {1}), LuaInvalidArgumentError);

    // null function
    ASSERT_THROW(LuaFunction("nullptr"s, nullptr).invoke(sPtr, {1}), LuaInvalidArgumentError);

    // nonexistent function
    ASSERT_THROW(LuaFunction("doesNotExist"s, funcPtr).invoke(sPtr, {1}), LuaInvalidStateError);

    // incompatible signature
    ASSERT_THROW(state.invoke("multiVariate", ParameterStack()), LuaCallError);

}

TEST(EchoTest, InvokeRawTest)
{
    auto state = LuaState(testDir + "identity.lua"s);
    lua_State* sPtr = state.expose();
    LuaFunction f = state.getFunction("identity");
    ParameterStack result;

    result = f.invoke(sPtr, {nullptr});
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Nil);

    result = f.invoke(sPtr, {true});
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Boolean);
    EXPECT_EQ(result.at(0)->asLuaBoolean().getValue(), true);

    result = f.invoke(sPtr, {getVoidPtr()});
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::LightUserData);
    EXPECT_EQ(result.at(0)->asLuaLightUserData().getValue(), funcPtr);

    result = f.invoke(sPtr, {1});
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Number);
    EXPECT_EQ(result.at(0)->asLuaNumber().getValue(), 1);

    result = f.invoke(sPtr, {"text"s});
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::String);
    EXPECT_EQ(result.at(0)->asLuaString().getValue(), "text");
}

TEST(EchoTest, InvokeMultiVariateTest)
{
    auto state = LuaState(testDir + "identity.lua"s);
    ParameterStack result;

    result = state.invoke("multiVariate", {1, 2});
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result.at(0)->getTypeId(), LuaTypeId::Number);
    ASSERT_EQ(result.at(1)->getTypeId(), LuaTypeId::Number);
    EXPECT_EQ(result.at(0)->asLuaNumber().getValue(), -1);
    EXPECT_EQ(result.at(1)->asLuaNumber().getValue(), +3);
}


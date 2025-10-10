#include <iostream>
#include <string>
using namespace std::string_literals;

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

constexpr auto testDir = "./testScripts/";

TEST(StateTest, BootupTest)
{
    EXPECT_THROW(LuaState(testDir + "doesNotExist.lua"s), LuaInitError);

    EXPECT_THROW(LuaState(testDir + "malformed.lua"s), LuaInitError);

    EXPECT_NO_THROW(LuaState(testDir + "globals.lua"s));

}

TEST(StateTest, ExtractGlobalsTest)
{
    auto state = LuaState(testDir + "globals.lua"s);

    EXPECT_EQ(state.getStackTopIndex(), 0);

    ASSERT_TRUE(state.hasGlobalSymbol("bool"));
    EXPECT_EQ(state.getGlobalSymbolType("bool"), LuaTypeId::Boolean);
    LuaEntity* boolean = state.getGlobalEntity("bool");
    EXPECT_EQ(boolean->asLuaBoolean().getValue(), true);
    delete boolean;

    ASSERT_TRUE(state.hasGlobalSymbol("nmbr"));
    EXPECT_EQ(state.getGlobalSymbolType("nmbr"), LuaTypeId::Number);
    LuaEntity* number = state.getGlobalEntity("nmbr");
    EXPECT_EQ(number->asLuaNumber().getValue(), 0);
    delete number;

    ASSERT_TRUE(state.hasGlobalSymbol("text"));
    EXPECT_EQ(state.getGlobalSymbolType("text"), LuaTypeId::String);
    LuaEntity* string = state.getGlobalEntity("text");
    EXPECT_EQ(string->asLuaString().getValue(), "string");
    delete string;

    ASSERT_TRUE(state.hasGlobalSymbol("data"));
    EXPECT_EQ(state.getGlobalSymbolType("data"), LuaTypeId::Table);
    LuaEntity* table = state.getGlobalEntity("data");
    ASSERT_EQ(table->asLuaTable().size(), 4);
    LuaEntity* tableEntry;
    {
        tableEntry = table->asLuaTable().find(LuaNumber(1));
        ASSERT_NE(tableEntry, nullptr);
        ASSERT_EQ(tableEntry->getTypeId(), LuaTypeId::Boolean);
        EXPECT_EQ(tableEntry->asLuaBoolean().getValue(), true);
    }
    {
        tableEntry = table->asLuaTable().find(LuaNumber(2));
        ASSERT_NE(tableEntry, nullptr);
        ASSERT_EQ(tableEntry->getTypeId(), LuaTypeId::Number);
        EXPECT_EQ(tableEntry->asLuaNumber().getValue(), 1);
    }
    {
        tableEntry = table->asLuaTable().find(LuaNumber(3));
        ASSERT_NE(tableEntry, nullptr);
        ASSERT_EQ(tableEntry->getTypeId(), LuaTypeId::String);
        EXPECT_EQ(tableEntry->asLuaString().getValue(), "text");
    }
    {
        tableEntry = table->asLuaTable().find(LuaNumber(4));
        ASSERT_NE(tableEntry, nullptr);
        ASSERT_EQ(tableEntry->getTypeId(), LuaTypeId::Table);
        EXPECT_EQ(tableEntry->asLuaTable().size(), 1);
        EXPECT_NE(tableEntry->asLuaTable().find(LuaString("key")), nullptr);
    }
    delete table;

    ASSERT_TRUE(state.hasGlobalSymbol("func"));
    EXPECT_EQ(state.getGlobalSymbolType("func"), LuaTypeId::Function);
    LuaEntity* function = state.getGlobalEntity("func");
    lua_CFunction luaFuncPtr = function->asLuaFunction().getPseudoFuncPtr();
    EXPECT_NE(luaFuncPtr, nullptr);
    delete function;

    LuaTable more;
    ASSERT_TRUE(state.hasGlobalSymbol("more"));
    EXPECT_EQ(state.getGlobalSymbolType("more"), LuaTypeId::Table);
    state.synchronizeWithGlobalSymbol(more, "more");
    EXPECT_EQ(more.size(), 1);
    {
        tableEntry = more.find(LuaString("foo"));
        ASSERT_NE(tableEntry, nullptr);
        ASSERT_EQ(tableEntry->getTypeId(), LuaTypeId::Function);
        EXPECT_EQ(tableEntry->asLuaFunction().getPseudoFuncPtr(), luaFuncPtr);
    }

    LuaNil nil;
    state.synchronizeWithGlobalSymbol(nil, "doesNotExist");

    EXPECT_EQ(state.getStackTopIndex(), 0);
}

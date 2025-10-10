#include <iostream>
#include <string>
using namespace std::string_literals;

#include <gtest/gtest.h>

#include <luawrapper.hpp>

#include "commonconversionutil.hpp"

using namespace LuaWrapper;

TEST(TypeSystemTest, getTypeId)
{
    // setup
    LuaNil              nil;
    LuaBoolean          boolean;
    LuaLightUserData    lud;
    LuaNumber           number;
    LuaString           string;
    LuaTable            table;
    LuaFunction         function;

    // expect
    EXPECT_EQ(nil.getTypeId(),              LuaTypeId::Nil);
    EXPECT_EQ(nil.getStaticTypeId(),        LuaTypeId::Nil);
    EXPECT_TRUE(nil.isNil());

    EXPECT_EQ(boolean.getTypeId(),          LuaTypeId::Boolean);
    EXPECT_EQ(boolean.getStaticTypeId(),    LuaTypeId::Boolean);
    EXPECT_TRUE(boolean.isBoolean());

    EXPECT_EQ(lud.getTypeId(),              LuaTypeId::LightUserData);
    EXPECT_EQ(lud.getStaticTypeId(),        LuaTypeId::LightUserData);
    EXPECT_TRUE(lud.isLightUserData());

    EXPECT_EQ(number.getTypeId(),           LuaTypeId::Number);
    EXPECT_EQ(number.getStaticTypeId(),     LuaTypeId::Number);
    EXPECT_TRUE(number.isNumber());

    EXPECT_EQ(string.getTypeId(),           LuaTypeId::String);
    EXPECT_EQ(string.getStaticTypeId(),     LuaTypeId::String);
    EXPECT_TRUE(string.isString());

    EXPECT_EQ(table.getTypeId(),            LuaTypeId::Table);
    EXPECT_EQ(table.getStaticTypeId(),      LuaTypeId::Table);
    EXPECT_TRUE(table.isTable());

    EXPECT_EQ(function.getTypeId(),            LuaTypeId::Function);
    EXPECT_EQ(function.getStaticTypeId(),      LuaTypeId::Function);
    EXPECT_TRUE(function.isFunction());
}

TEST(TypeSystemTest, DefaultAssignments)
{
    // setup
    LuaNil              nil;
    LuaBoolean          boolean;
    LuaLightUserData    lud;
    LuaNumber           number;
    LuaString           string;
    // TODO: LuaTable            table;

    // when
    nil = nullptr;
    boolean = false;
    lud =  getVoidPtr();
    number = 1;
    string = "string";

    // then
    EXPECT_EQ(nil.getValue(), nullptr);
    EXPECT_EQ(boolean.getValue(), false);
    EXPECT_EQ(lud.getValue(), getVoidPtr());
    EXPECT_EQ(number.getValue(), 1);
    EXPECT_EQ(string.getValue(), "string"s);
}

TEST(TypeSystemTest, ParameterStack_ImplicitConversion)
{
    // when
    ParameterStack ps =
    {
        nullptr,
        true,
        getVoidPtr(),
        1,
        1.0,
        "char literal",
        "string literal"s
    };

    // then
    ASSERT_EQ(ps.empty(), false);
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
        // std::cout << param->to_string() << std::endl;
    }
}

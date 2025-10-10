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

// TODO: move this to own test suite?
TEST(TypeSystemTest, ParameterStack_BuilderInterface)
{
    // setup
    const int NAddedItems = 14;
    const void* ptrLUD = getVoidPtr();

    LuaNil              nil;
    LuaBoolean          lBoolean;
    LuaTrivialType      tBoolean = true;
    LuaLightUserData    lLUD = ptrLUD;
    LuaTrivialType      tLUD = ptrLUD;
    LuaNumber           lNumber = -1;
    LuaTrivialType      tNumberI = -1;
    LuaTrivialType      tNumberD = -1.0;
    LuaString           lcString = "LuaString for copy";
    LuaString           lmString = "LuaString for move";
    LuaTrivialType      tlString = "literal string for copy";
    LuaTrivialType      tscString = "std::string for copy"s;
    LuaTrivialType      tsmString = "std::string for move"s;

    const auto preMove = lmString.c_str();

    // when
    ParameterStack ps;
    ps
    /*  0 */ .addEntity(nil)
    /*  1 */ .addEntity(nullptr)
    /*  2 */ .addEntity(std::move(lBoolean))
    /*  3 */ .addEntity(tBoolean)
    /*  4 */ .addEntity(lLUD)
    /*  5 */ .addEntity(tLUD)
    /*  6 */ .addEntity(lNumber)
    /*  7 */ .addEntity(tNumberD)
    /*  8 */ .addEntity(tNumberI)
    /*  9 */ .addEntity(lcString)
    /* 10 */ .addEntity(std::move(lmString))
    /* 11 */ .addEntity(tlString)
    /* 12 */ .addEntity(tscString)
    /* 13 */ .addEntity(std::move(tsmString))
    ;

    const auto aftMove = lmString.c_str();
    const auto newInst = ps.at(10)->asLuaString().c_str();

    // then
    EXPECT_EQ(preMove, newInst);

    ASSERT_FALSE(ps.empty());
    EXPECT_EQ(ps.size(), NAddedItems);
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
        // std::cout << param->to_string() << std::endl;
    }

    EXPECT_EQ(lcString.getValue(), "LuaString for copy");

    ASSERT_THROW(ps.at(-1), LuaInvalidArgumentError);

    ASSERT_THROW(ps.at(NAddedItems), LuaInvalidArgumentError);

    ASSERT_NO_THROW(ps.at(NAddedItems - 1));

    ASSERT_NO_THROW(ps.at(0)->getTypeId());

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

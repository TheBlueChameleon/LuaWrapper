#include <iostream>
#include <string>
using namespace std::string_literals;

#include <gtest/gtest.h>

#include <luawrapper.hpp>

#include "commonconversionutil.hpp"

using namespace LuaWrapper;

TEST(ParamStackTest, ParameterStack_BuilderInterface)
{
    // setup
    const int NAddedItems = 14;
    const void* ptrLUD = getVoidPtr();

    LuaNil              nil;
    LuaBoolean          lBoolean;
    LuaWrappableType    tBoolean = true;
    LuaLightUserData    lLUD = ptrLUD;
    LuaWrappableType    tLUD = ptrLUD;
    LuaNumber           lNumber = -1;
    LuaWrappableType    tNumberI = -1;
    LuaWrappableType    tNumberD = -1.0;
    LuaString           lcString = "LuaString for copy";
    LuaString           lmString = "LuaString for move";
    LuaWrappableType    tlString = "literal string for copy";
    LuaWrappableType    tscString = "std::string for copy"s;
    LuaWrappableType    tsmString = "std::string for move"s;

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

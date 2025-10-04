#include <iostream>

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

TEST(TypeSystemTest, getTypeTest)
{
    // setup
    LuaNil nil;
    LuaBoolean boolean;

    // expect
    EXPECT_EQ(nil.getTypeId(), LuaTypeID::Nil);
    EXPECT_EQ(nil.getStaticTypeId(), LuaTypeID::Nil);

    EXPECT_EQ(boolean.getTypeId(), LuaTypeID::Boolean);
    EXPECT_EQ(boolean.getStaticTypeId(), LuaTypeID::Boolean);
}

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

TEST(TypeSystemTest, getTypeTest)
{
    // setup
    LuaNil nil;
    LuaBoolean boolean;

    // expect
    EXPECT_EQ(nil.getType(), LuaTypeID::Nil);
    EXPECT_EQ(boolean.getType(), LuaTypeID::Boolean);
}

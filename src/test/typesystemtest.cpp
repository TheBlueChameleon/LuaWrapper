#include <iostream>

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

TEST(TypeSystemTest, getTypeId)
{
    // setup
    LuaNil nil;
    LuaBoolean boolean;

    // expect
    EXPECT_EQ(nil.getTypeId(), LuaTypeId::Nil);
    EXPECT_EQ(nil.getStaticTypeId(), LuaTypeId::Nil);

    EXPECT_EQ(boolean.getTypeId(), LuaTypeId::Boolean);
    EXPECT_EQ(boolean.getStaticTypeId(), LuaTypeId::Boolean);
}

TEST(TypeSystemTest, ParameterStack_BuilderInterface)
{
    // setup
    LuaNil nil;
    LuaBoolean boolean;

    // when
    ParameterStack ps;

    // then
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
    }
}

void foo() {}

TEST(TypeSystemTest, ParameterStack_ImplicitConversion)
{
    // when
    ParameterStack ps = {nullptr, true/*, (void*)foo*/};

    //     ps2.withNil();
    //     ps2.withBoolean(true);

    // then
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
    }
}

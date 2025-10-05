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
    const int NAddedItems = 4;
    LuaNil nil;
    LuaBoolean boolean;
    LuaTrivialType TRUE = true;

    // when
    ParameterStack ps;
    ps
    .addEntity(nil)
    .addEntity(std::move(boolean))
    .addEntity(nullptr)
    .addEntity(TRUE);

    // then
    ASSERT_FALSE(ps.empty());
    EXPECT_EQ(ps.size(), NAddedItems);
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
        std::cout << param->repr() << std::endl;
    }

    ASSERT_THROW(ps.at(-1), LuaInvalidArgumentError);

    ASSERT_THROW(ps.at(NAddedItems), LuaInvalidArgumentError);

    ASSERT_NO_THROW(ps.at(NAddedItems - 1));

    ASSERT_NO_THROW(ps.at(0)->getTypeId());

}

void foo() {}

TEST(TypeSystemTest, ParameterStack_ImplicitConversion)
{
    // when
    ParameterStack ps = {nullptr, true/*, (void*)foo*/};

    // then
    ASSERT_EQ(ps.empty(), false);
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
        std::cout << param->repr() << std::endl;
    }
}

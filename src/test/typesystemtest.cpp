#include <iostream>

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

TEST(TypeSystemTest, getTypeId)
{
    // setup
    LuaNil              nil;
    LuaBoolean          boolean;
    LuaLightUserData    lud;
    LuaNumber           number;

    // expect
    EXPECT_EQ(nil.getTypeId(),              LuaTypeId::Nil);
    EXPECT_EQ(nil.getStaticTypeId(),        LuaTypeId::Nil);

    EXPECT_EQ(boolean.getTypeId(),          LuaTypeId::Boolean);
    EXPECT_EQ(boolean.getStaticTypeId(),    LuaTypeId::Boolean);

    EXPECT_EQ(lud.getTypeId(),              LuaTypeId::LightUserData);
    EXPECT_EQ(lud.getStaticTypeId(),        LuaTypeId::LightUserData);

    EXPECT_EQ(number.getTypeId(),           LuaTypeId::Number);
    EXPECT_EQ(number.getStaticTypeId(),     LuaTypeId::Number);
}

TEST(TypeSystemTest, ParameterStack_BuilderInterface)
{
    // setup
    const int NAddedItems = 7;
    LuaNil          nil;
    LuaBoolean      lBoolean;
    LuaTrivialType  tBoolean = true;
    LuaNumber       lNumber = -1;
    LuaTrivialType  tNumberI = -1;
    LuaTrivialType  tNumberD = -1.0;

    // when
    ParameterStack ps;
    ps
    .addEntity(nil)
    .addEntity(std::move(lBoolean))
    .addEntity(nullptr)
    .addEntity(tBoolean)
    .addEntity(lNumber)
    .addEntity(tNumberD)
    .addEntity(tNumberI)
    ;

    // then
    ASSERT_FALSE(ps.empty());
    EXPECT_EQ(ps.size(), NAddedItems);
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
        std::cout << param->to_string() << std::endl;
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
    ParameterStack ps = {nullptr, true, (void*)foo};

    // then
    ASSERT_EQ(ps.empty(), false);
    for (const auto& param : ps)
    {
        ASSERT_NE(param->getTypeId(), LuaTypeId::None);
        std::cout << param->to_string() << std::endl;
    }
}

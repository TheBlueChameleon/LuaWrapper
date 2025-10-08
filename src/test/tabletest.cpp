#include <iostream>
#include <string>
using namespace std::string_literals;

#include <gtest/gtest.h>

#include <luawrapper.hpp>

using namespace LuaWrapper;

TEST(TableTest, LuaTableMethods)
{
    LuaNil              nil;
    LuaBoolean          boolean;
    LuaLightUserData    lud;
    LuaNumber           number;
    LuaString           string = "str";
    LuaString           other  = "oth";
    LuaTable            table;

    ASSERT_EQ(table.size(), 0);
    ASSERT_TRUE(table.empty());

    // forbidden key types throw
    ASSERT_THROW(table.insert(nil, table), LuaInvalidArgumentError);

    ASSERT_THROW(table.insert(boolean, table), LuaInvalidArgumentError);

    ASSERT_THROW(table.insert(table, table), LuaInvalidArgumentError);

    // allowed key types do not throw and return true on insert
    EXPECT_TRUE(table.insert(lud, nil));
    EXPECT_TRUE(table.insert(number, number));
    EXPECT_TRUE(table.insert(string, other));
    EXPECT_FALSE(table.insert(string, string));
    EXPECT_TRUE(table.insert(other, string));

    EXPECT_EQ(table.size(), 4);
    EXPECT_EQ(*table.find(string), other);

    table.erase(other);
    EXPECT_EQ(table.size(), 3);
}

TEST(TableTest, NestedTableRepr)
{
    LuaTable            outer;
    LuaTable            middle;
    LuaTable            inner;
    LuaTable            empty;

    inner.insert(LuaString("thy"), LuaString("bar"));
    middle.insert(LuaString("foo"), inner);
    outer.insert(LuaString("key"), middle);
    outer.insert(LuaString("M_T"), empty);

    /* yes, I do know about raw strings. BUT.
     * notice the whitespaces at the end of some lines?
     * yeah, IDEs don't like trailing whitespaces.
     */
    const auto expected = "{ TABLE:\n"
                          "  M_T : \n"
                          "  { TABLE:\n"
                          "  }\n"
                          "  key : \n"
                          "  { TABLE:\n"
                          "    foo : \n"
                          "    { TABLE:\n"
                          "      thy : bar\n"
                          "    }\n"
                          "  }\n"
                          "}\n";
    EXPECT_EQ(outer.to_string(), expected);
}

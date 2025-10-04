#ifndef LUATYPES_H
#define LUATYPES_H

#include <string>

#include "luacapi.hpp"

namespace LuaWrapper
{
    enum class LuaTypeID
    {
        None = LUA_TNONE,

        Nil = LUA_TNIL,
        Boolean = LUA_TBOOLEAN,
        LightUserData = LUA_TLIGHTUSERDATA,
        Number = LUA_TNUMBER,
        String = LUA_TSTRING,
        Table = LUA_TTABLE,
        Function= LUA_TFUNCTION,
        UserData = LUA_TUSERDATA,
        Thread = LUA_TTHREAD,

        NumberOfTypes = LUA_NUMTYPES,
    };

    std::string getTypeName(const int typeId);
    std::string getTypeName(const LuaTypeID typeId);
}

#endif // LUATYPES_H

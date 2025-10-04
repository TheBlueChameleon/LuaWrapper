#include <string>
using namespace std::string_literals;

#include "luacapi.hpp"
#include "luatypes.hpp"
#include "luaerror.hpp"

namespace LuaWrapper
{
    std::string getTypeName(const int typeId)
    {
        switch (typeId)
        {
            case LUA_TNONE:
                return "(unknown type)";
            case LUA_TNIL:
                return "Nil";
            case LUA_TBOOLEAN:
                return "Boolean";
            case LUA_TLIGHTUSERDATA:
                return "Light User Data";
            case LUA_TNUMBER:
                return "Number";
            case LUA_TSTRING:
                return "String";
            case LUA_TTABLE:
                return "Table";
            case LUA_TFUNCTION:
                return "Function";
            case LUA_TUSERDATA:
                return "User Data";
            case LUA_TTHREAD:
                return "Thread";

            // case LUA_NUMTYPES:
            //     return ???;

            default:
                throw std::invalid_argument(
                    "Unknown TypeID: "s + std::to_string(typeId)
                );
        }
    }

    std::string getTypeName(const LuaTypeID typeId)
    {
        return getTypeName(static_cast<int>(typeId));
    }
}





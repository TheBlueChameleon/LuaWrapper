#include <string>
using namespace std::string_literals;

#include "luacapi.hpp"
#include "luatypes.hpp"
#include "luaerror.hpp"

namespace LuaWrapper
{
    LuaTypeId::LuaTypeId() :
        typeId(None)
    {}

    LuaTypeId::LuaTypeId(int typeId) :
        typeId(typeId)
    {
        if ((typeId < None) || (typeId >= NumberOfTypes))
        {
            throw LuaInvalidArgumentError(
                "Unknown TypeId: "s + std::to_string(typeId)
            );
        }
    }

    std::string LuaTypeId::getTypeName() const
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

            default:
                throw LuaInvalidArgumentError(
                    "Unknown TypeId: "s + std::to_string(typeId)
                );
        }
    }

    std::string LuaTypeId::getTypeName(const int typeId)
    {
        return LuaTypeId(typeId).getTypeName();
    }

    bool LuaTypeId::operator==(const LuaTypeId other) const
    {
        return typeId == other.typeId;
    }

    // ====================================================================== //

    std::string LuaTrivialType::getTrivialTypeName() const
    {
        switch (index())
        {
            case LuaTrivialType::Nil:
                return "null pointer";
            case LuaTrivialType::Boolean:
                return "boolean";
            case LuaTrivialType::LightUserData:
                return "void pointer";
            case LuaTrivialType::Integer:
                return "integer";
            case LuaTrivialType::Double:
                return "double";
            case LuaTrivialType::CharPtr:
                return "char pointer";
            case LuaTrivialType::String:
                return "string";

            default:
                throw LuaTypeError(
                    "Unknown Trivial Type ID: "s + std::to_string(index())
                );
        }
    }



}





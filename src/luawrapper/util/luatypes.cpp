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

    LuaTypeId::LuaTypeId(const int typeId) :
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

    LuaTypeId::operator int() const
    {
        return typeId;
    }

    bool LuaTypeId::operator==(const LuaTypeId other) const
    {
        return typeId == other.typeId;
    }

    bool LuaTypeId::operator==(const int other) const
    {
        return typeId == other;
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

    void assertType(const LuaTrivialType* value, const int expectedTypeId)
    {
        if (value->index() != expectedTypeId)
        {
            throw LuaTypeError(
                "Could not convert wrapped "s + value->getTrivialTypeName() + " "
                "to typeId " + std::to_string(expectedTypeId)
            );
        }
    }

    nullptr_t LuaTrivialType::getAsNil() const
    {
        assertType(this, LuaTrivialType::Nil);
        return nullptr;
    }

    int LuaTrivialType::getAsInt() const
    {
        assertType(this, LuaTrivialType::Integer);
        return std::get<LuaTrivialType::Integer>(*this);
    }

}





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

    std::string LuaWrappableType::getTrivialTypeName() const
    {
        switch (index())
        {
            case LuaWrappableType::Nil:
                return "null pointer";
            case LuaWrappableType::Boolean:
                return "boolean";
            case LuaWrappableType::LightUserData:
                return "void pointer";
            case LuaWrappableType::Integer:
                return "integer";
            case LuaWrappableType::Double:
                return "double";
            case LuaWrappableType::CharPtr:
                return "char pointer";
            case LuaWrappableType::String:
                return "string";

            default:
                throw LuaTypeError(
                    "Unknown Trivial Type ID: "s + std::to_string(index())
                );
        }
    }

    void assertType(const LuaWrappableType* value, const int expectedTypeId)
    {
        if (value->index() != expectedTypeId)
        {
            throw LuaTypeError(
                "Could not convert wrapped "s + value->getTrivialTypeName() + " "
                "to typeId " + std::to_string(expectedTypeId)
            );
        }
    }

    nullptr_t LuaWrappableType::getAsNil() const
    {
        assertType(this, LuaWrappableType::Nil);
        return nullptr;
    }

    bool LuaWrappableType::getAsBoolean() const
    {
        assertType(this, LuaWrappableType::Boolean);
        return std::get<LuaWrappableType::Boolean>(*this);
    }

    void *LuaWrappableType::getAsLightUserData() const
    {
        assertType(this, LuaWrappableType::LightUserData);
        return std::get<LuaWrappableType::LightUserData>(*this);
    }

    int LuaWrappableType::getAsInteger() const
    {
        assertType(this, LuaWrappableType::Integer);
        return std::get<LuaWrappableType::Integer>(*this);
    }

    double LuaWrappableType::getAsDouble() const
    {
        assertType(this, LuaWrappableType::Double);
        return std::get<LuaWrappableType::Double>(*this);
    }

    const char* LuaWrappableType::getAsCharPtr() const
    {
        assertType(this, LuaWrappableType::CharPtr);
        return std::get<LuaWrappableType::CharPtr>(*this);
    }

    const std::string& LuaWrappableType::getAsString() const
    {
        assertType(this, LuaWrappableType::String);
        return std::get<LuaWrappableType::String>(*this);
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaTypeId>::operator()(const LuaWrapper::LuaTypeId& typeId) const
    {
        return typeId;
    }
}

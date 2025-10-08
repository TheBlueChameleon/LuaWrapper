#include <string>
using namespace std::string_literals;

#include "luaentityfactory.hpp"
#include "entities.hpp"
#include "../util/luautil.hpp"

namespace LuaWrapper
{
    // ...................................................................... //
    // from typeId

    LuaEntity* LuaEntityFactory::makeLuaEntityFromTypeId(const LuaTypeId typeId)
    {
        switch (typeId)
        {
            case LuaTypeId::None:
                throw LuaInvalidArgumentError(
                    "Cannot make Lua entity of type "s + typeId.getTypeName()
                );

            case LuaTypeId::Nil:
                return new LuaNil();
            case LuaTypeId::Boolean:
                return new LuaBoolean();
            case LuaTypeId::LightUserData:
                return new LuaLightUserData();
            case LuaTypeId::Number:
                return new LuaNumber();
            case LuaTypeId::String:
                return new LuaString();
            case LuaTypeId::Table:
                return new LuaTable();
            case LuaTypeId::Function:
            case LuaTypeId::UserData:
            case LuaTypeId::Thread:
                throw LuaNotImplementedError(
                    "Not yet implemented: constructing Lua Entity from "s + typeId.getTypeName()
                );

            default:
                throw LuaInvalidArgumentError(
                    "Cannot make Lua entity with type id "s + std::to_string(typeId)
                );
        }
    }

    // ...................................................................... //
    // from C++ types

    LuaEntity* LuaEntityFactory::makeLuaEntity(const nullptr_t value)
    {
        return new LuaNil();
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const bool value)
    {
        return new LuaBoolean(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const void* value)
    {
        return new LuaLightUserData(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const int value)
    {
        return new LuaNumber(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const double value)
    {
        return new LuaNumber(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const char* value)
    {
        return new LuaString(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const std::string& value)
    {
        return new LuaString(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(std::string&& value)
    {
        return new LuaString(std::move(value));
    }

    // ...................................................................... //
    // from variant

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaTrivialType& value)
    {
        switch (value.index())
        {
            case LuaTrivialType::Nil:
                return LuaEntityFactory::makeLuaEntity();
            case LuaTrivialType::Boolean:
                return LuaEntityFactory::makeLuaEntity(value.getAsBoolean());
            case LuaTrivialType::LightUserData:
                return LuaEntityFactory::makeLuaEntity(value.getAsLightUserData());
            case LuaTrivialType::Integer:
                return LuaEntityFactory::makeLuaEntity(value.getAsInteger());
            case LuaTrivialType::Double:
                return LuaEntityFactory::makeLuaEntity(value.getAsDouble());
            case LuaTrivialType::CharPtr:
                return LuaEntityFactory::makeLuaEntity(value.getAsCharPtr());
            case LuaTrivialType::String:
                return LuaEntityFactory::makeLuaEntity(value.getAsString());

            default:
                throw LuaTypeError(
                    "Unknown Trivial Type ID: "s + std::to_string(value.index())
                );
        }
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaTrivialType&& value)
    {
        switch (value.index())
        {
            case LuaTrivialType::Nil:
                return LuaEntityFactory::makeLuaEntity();
            case LuaTrivialType::Boolean:
                return LuaEntityFactory::makeLuaEntity(value.getAsBoolean());
            case LuaTrivialType::LightUserData:
                return LuaEntityFactory::makeLuaEntity(value.getAsLightUserData());
            case LuaTrivialType::Integer:
                return LuaEntityFactory::makeLuaEntity(value.getAsInteger());
            case LuaTrivialType::Double:
                return LuaEntityFactory::makeLuaEntity(value.getAsDouble());
            case LuaTrivialType::CharPtr:
                return LuaEntityFactory::makeLuaEntity(value.getAsCharPtr());
            case LuaTrivialType::String:
                return LuaEntityFactory::makeLuaEntity(std::move(value.getAsString()));

            default:
                throw LuaTypeError(
                    "Unknown Trivial Type ID: "s + std::to_string(value.index())
                );
        }
    }

    // ...................................................................... //
    // from LuaEntity

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaNil& value)
    {
        return new LuaNil(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaNil&& value)
    {
        return new LuaNil(std::move(value));
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaBoolean& value)
    {
        return new LuaBoolean(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaBoolean&& value)
    {
        return new LuaBoolean(std::move(value));
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaLightUserData& value)
    {
        return new LuaLightUserData(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaLightUserData&& value)
    {
        return new LuaLightUserData(std::move(value));
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaNumber& value)
    {
        return new LuaNumber(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaNumber&& value)
    {
        return new LuaNumber(std::move(value));
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaString& value)
    {
        return new LuaString(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaString&& value)
    {
        return new LuaString(std::move(value));
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaTable& value)
    {
        return new LuaTable(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaTable&& value)
    {
        return new LuaTable(std::move(value));
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaFunction& value)
    {
        return new LuaFunction(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaFunction&& value)
    {
        return new LuaFunction(std::move(value));
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaEntity& value)
    {
        switch (value.getTypeId())
        {
            case LuaTypeId::None:
                throw LuaInvalidArgumentError(
                    "Cannot make Lua entity of type "s + value.getTypeId().getTypeName()
                );

            case LuaTypeId::Nil:
                return LuaEntityFactory::makeLuaEntity();
            case LuaTypeId::Boolean:
                return LuaEntityFactory::makeLuaEntity(value.asLuaBoolean());
            case LuaTypeId::LightUserData:
                return LuaEntityFactory::makeLuaEntity(value.asLuaLightUserData());
            case LuaTypeId::Number:
                return LuaEntityFactory::makeLuaEntity(value.asLuaNumber());
            case LuaTypeId::String:
                return LuaEntityFactory::makeLuaEntity(value.asLuaString());
            case LuaTypeId::Table:
                return LuaEntityFactory::makeLuaEntity(value.asLuaTable());
            case LuaTypeId::Function:
                return LuaEntityFactory::makeLuaEntity(value.asLuaFunction());
            case LuaTypeId::UserData:
            case LuaTypeId::Thread:
                throw LuaNotImplementedError(
                    "Not yet implemented: copy-constructing Lua Entity from "s + value.getTypeId().getTypeName()
                );

            default:
                throw LuaInvalidArgumentError(
                    "Cannot make Lua entity with type id "s + std::to_string(value.getTypeId())
                );
        }
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(LuaEntity&& value)
    {
        switch (value.getTypeId())
        {
            case LuaTypeId::None:
                throw LuaInvalidArgumentError(
                    "Cannot make Lua entity of type "s + value.getTypeId().getTypeName()
                );

            case LuaTypeId::Nil:
                return LuaEntityFactory::makeLuaEntity();
            case LuaTypeId::Boolean:
                return LuaEntityFactory::makeLuaEntity(value.asLuaBoolean());
            case LuaTypeId::LightUserData:
                return LuaEntityFactory::makeLuaEntity(value.asLuaLightUserData());
            case LuaTypeId::Number:
                return LuaEntityFactory::makeLuaEntity(value.asLuaNumber());
            case LuaTypeId::String:
                return LuaEntityFactory::makeLuaEntity(std::move(value.asLuaString()));
            case LuaTypeId::Table:
                return LuaEntityFactory::makeLuaEntity(std::move(value.asLuaTable()));
            case LuaTypeId::Function:
            case LuaTypeId::UserData:
            case LuaTypeId::Thread:
                throw LuaNotImplementedError(
                    "Not yet implemented: move-constructing Lua Entity from "s + value.getTypeId().getTypeName()
                );

            default:
                throw LuaInvalidArgumentError(
                    "Cannot make Lua entity with type id "s + std::to_string(value.getTypeId())
                );
        }
    }
}

#include <string>
using namespace std::string_literals;

#include "luaentityfactory.hpp"
#include "entities.hpp"
#include "../util/luautil.hpp"

namespace LuaWrapper
{
    LuaEntityFactory::LuaEntityFactory() {}

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
            case LuaTrivialType::String:
                throw LuaNotImplementedError(
                    "Not yet implemented: copy-constructing Lua Entity from "s + value.getTrivialTypeName()
                );

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
            case LuaTrivialType::String:
                throw LuaNotImplementedError(
                    "Not yet implemented: move-constructing Lua Entity from "s + value.getTrivialTypeName()
                );

            default:
                throw LuaTypeError(
                    "Unknown Trivial Type ID: "s + std::to_string(value.index())
                );
        }
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
                return LuaEntityFactory::makeLuaEntity(value.asLuaBoolean().getValue());
            case LuaTypeId::LightUserData:
                return LuaEntityFactory::makeLuaEntity(value.asLuaLightUserData().getValue());
            case LuaTypeId::Number:
                return LuaEntityFactory::makeLuaEntity(value.asLuaNumber().getValue());
            case LuaTypeId::String:
            case LuaTypeId::Table:
            case LuaTypeId::Function:
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
                return LuaEntityFactory::makeLuaEntity(value.asLuaBoolean().getValue());
            case LuaTypeId::LightUserData:
                return LuaEntityFactory::makeLuaEntity(value.asLuaLightUserData().getValue());
            case LuaTypeId::Number:
                return LuaEntityFactory::makeLuaEntity(value.asLuaNumber().getValue());
            case LuaTypeId::String:
            case LuaTypeId::Table:
            case LuaTypeId::Function:
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
}

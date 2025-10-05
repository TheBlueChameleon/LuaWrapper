#include <string>
using namespace std::string_literals;

#include "luaentityfactory.hpp"
#include "entities.hpp"
#include "../util/luautil.hpp"

namespace LuaWrapper
{
    LuaEntityFactory::LuaEntityFactory() {}

    LuaEntity* LuaEntityFactory::makeLuaNil(const nullptr_t value)
    {
        return new LuaNil();
    }

    LuaEntity* LuaEntityFactory::makeLuaBoolean(const bool value)
    {
        return new LuaBoolean(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaLightUserData(const void* value)
    {
        return new LuaLightUserData(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaNumber(const double value)
    {
        return new LuaNumber(value);
    }

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaTrivialType& value)
    {
        switch (value.index())
        {
            case LuaTrivialType::Nil:
                return LuaEntityFactory::makeLuaNil();
            case LuaTrivialType::Boolean:
                return LuaEntityFactory::makeLuaBoolean(std::get<LuaTrivialType::Boolean>(value));
            case LuaTrivialType::LightUserData:
                return LuaEntityFactory::makeLuaLightUserData(std::get<LuaTrivialType::LightUserData>(value));
            case LuaTrivialType::Integer:
                return LuaEntityFactory::makeLuaNumber(std::get<LuaTrivialType::Integer>(value));
            case LuaTrivialType::Double:
                return LuaEntityFactory::makeLuaNumber(std::get<LuaTrivialType::Double>(value));
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
                return LuaEntityFactory::makeLuaNil();
            case LuaTrivialType::Boolean:
                return LuaEntityFactory::makeLuaBoolean(std::get<LuaTrivialType::Boolean>(value));
            case LuaTrivialType::LightUserData:
                return LuaEntityFactory::makeLuaLightUserData(std::get<LuaTrivialType::LightUserData>(value));
            case LuaTrivialType::Integer:
                return LuaEntityFactory::makeLuaNumber(std::get<LuaTrivialType::Integer>(value));
            case LuaTrivialType::Double:
                return LuaEntityFactory::makeLuaNumber(std::get<LuaTrivialType::Double>(value));
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
                return LuaEntityFactory::makeLuaNil();
            case LuaTypeId::Boolean:
                return LuaEntityFactory::makeLuaBoolean(value.asLuaBoolean().getValue());
            case LuaTypeId::LightUserData:
                return LuaEntityFactory::makeLuaLightUserData(value.asLuaLightUserData().getValue());
            case LuaTypeId::Number:
                return LuaEntityFactory::makeLuaNumber(value.asLuaNumber().getValue());
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
                return LuaEntityFactory::makeLuaNil();
            case LuaTypeId::Boolean:
                return LuaEntityFactory::makeLuaBoolean(value.asLuaBoolean().getValue());
            case LuaTypeId::LightUserData:
                return LuaEntityFactory::makeLuaLightUserData(value.asLuaLightUserData().getValue());
            case LuaTypeId::Number:
                return LuaEntityFactory::makeLuaNumber(value.asLuaNumber().getValue());
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

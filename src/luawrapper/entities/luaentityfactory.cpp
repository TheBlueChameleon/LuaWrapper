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

    LuaEntity* LuaEntityFactory::makeLuaEntity(const LuaTrivialType& value)
    {
        switch (value.index())
        {
            case LuaTrivialType::Nil:
                return new LuaNil();
            case LuaTrivialType::Boolean:
                return new LuaBoolean(std::get<LuaTrivialType::Boolean>(value));
            case LuaTrivialType::LightUserData:
            case LuaTrivialType::Integer:
            case LuaTrivialType::Double:
            case LuaTrivialType::CharPtr:
            case LuaTrivialType::String:
                throw LuaNotImplementedError(
                    "Not yet implemented: making Lua Entity from "s + value.getTrivialTypeName()
                );

            default:
                throw LuaTypeError(
                    "Unknown Trivial Type ID: "s + std::to_string(value.index())
                );
        }
    }
}

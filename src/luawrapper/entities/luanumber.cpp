#include "luanumber.hpp"

namespace LuaWrapper
{
    LuaNumber::LuaNumber() :
        LuaNumber(0.0)
    {}

    LuaNumber::LuaNumber(const double value) :
        LuaEntity(LuaTypeId::Number, value)
    {}

    LuaTypeId LuaNumber::getStaticTypeId()
    {
        return LuaTypeId::Number;
    }

    bool LuaNumber::isNumber() const
    {
        return true;
    }

    double LuaNumber::getValue() const
    {
        if (value.index() == LuaWrappableType::Integer)
        {
            return static_cast<double>(value.getAsInteger());
        }
        else
        {
            return value.getAsDouble();
        }
    }

    void LuaNumber::setValue(double newValue)
    {
        value = newValue;
    }

    bool LuaNumber::operator==(const LuaNumber& other) const
    {
        return value == other.value;
    }

    void LuaNumber::pushToLua(lua_State* L) const
    {
        if (value.index() == LuaWrappableType::Integer)
        {
            lua_pushinteger(L, value.getAsInteger());
        }
        else
        {
            lua_pushnumber(L, value.getAsDouble());
        }
    }

    void LuaNumber::fetchFromLua(lua_State* L)
    {
        value = lua_tonumber(L, -1);
    }

    std::string LuaNumber::to_string() const
    {
        if (value.index() == LuaWrappableType::Integer)
        {
            return std::to_string(value.getAsInteger());
        }
        else
        {
            return std::to_string(value.getAsDouble());
        }
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaNumber>::operator()(const LuaWrapper::LuaNumber& luaEntity) const
    {
        return std::hash<double>()(luaEntity.getValue());
    }
}

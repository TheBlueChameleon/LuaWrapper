#include "luanumber.hpp"

namespace LuaWrapper
{
    LuaNumber::LuaNumber() :
        LuaNumber(0.0)
    {}

    LuaNumber::LuaNumber(const double value) :
        LuaEntity(LuaTypeId::Number),
        value(value)
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
        return value;
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
        lua_pushnumber(L, value);
    }

    void LuaNumber::fetchFromLua(lua_State* L)
    {
        value = lua_tonumber(L, -1);
    }

    std::string LuaNumber::to_string() const
    {
        return std::to_string(value);
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaNumber>::operator()(const LuaWrapper::LuaNumber& luaEntity) const
    {
        return std::hash<double>()(luaEntity.getValue());
    }
}

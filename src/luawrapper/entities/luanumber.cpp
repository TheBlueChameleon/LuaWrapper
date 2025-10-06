#include "luanumber.hpp"

namespace LuaWrapper
{

    LuaNumber::LuaNumber(const double value) :
        LuaEntity(LuaTypeId::Number),
        value(value)
    {}

    LuaTypeId LuaNumber::getStaticTypeId()
    {
        return LuaTypeId::Number;
    }

    void LuaNumber::pushToLua(lua_State* L) const
    {

    }

    void LuaNumber::fetchFromLua(lua_State* L)
    {

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

    std::string LuaNumber::to_string() const
    {
        return std::to_string(value);
    }

    bool LuaNumber::operator==(const LuaNumber& other) const
    {
        return value == other.value;
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaNumber>::operator()(const LuaWrapper::LuaNumber& luaEntity) const
    {
        return std::hash<double>()(luaEntity.getValue());
    }
}

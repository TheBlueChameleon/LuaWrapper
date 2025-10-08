#include "luastring.hpp"

namespace LuaWrapper
{
    LuaString::LuaString() :
        LuaString("")
    {}

    LuaString::LuaString(const char* value) :
        LuaEntity(LuaTypeId::String),
        value(value)
    {}

    LuaString::LuaString(const std::string& value) :
        LuaEntity(LuaTypeId::String),
        value(value)
    {}

    LuaString::LuaString(std::string&& value) :
        LuaEntity(LuaTypeId::String),
        value(std::move(value))
    {}

    LuaString::LuaString(LuaString&& other) :
        LuaString(std::move(other.value))
    {}

    LuaString& LuaString::operator=(LuaString&& other)
    {
        this->value = std::move(other.value);
        return *this;
    }

    LuaTypeId LuaString::getStaticTypeId()
    {
        return LuaTypeId::String;
    }

    bool LuaString::isString() const
    {
        return true;
    }

    const std::string& LuaString::getValue() const
    {
        return value;
    }

    void LuaString::setValue(const std::string& newValue)
    {
        value = newValue;
    }

    void LuaString::setValue(std::string&& newValue)
    {
        value = std::move(newValue);
    }

    const char* LuaString::c_str() const
    {
        return value.c_str();
    }

    bool LuaString::operator==(const LuaString& other) const
    {
        return value == other.value;
    }

    void LuaString::pushToLua(lua_State* L) const
    {
        lua_pushstring(L, value.c_str());
    }

    void LuaString::fetchFromLua(lua_State* L)
    {
        value = lua_tostring(L, -1);
    }

    std::string LuaString::to_string() const
    {
        return value;
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaString>::operator()(const LuaWrapper::LuaString& luaEntity) const
    {
        return std::hash<std::string>()(luaEntity.getValue());
    }
}

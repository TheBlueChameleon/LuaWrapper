#ifndef LUASTRING_HPP
#define LUASTRING_HPP

#include <string>

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaString : public LuaEntity
    {
        public:
            LuaString();
            LuaString(const char* value);
            LuaString(const std::string& value);
            LuaString(std::string&& value);

            LuaString(const LuaString& other) = default;
            LuaString(LuaString&& other);
            LuaString& operator=(const LuaString& other) = default;
            LuaString& operator=(LuaString&& other) = default;

            static LuaTypeId getStaticTypeId();

            bool isString() const;

            const std::string& getValue() const;
            void               setValue(const std::string& newValue);
            void               setValue(std::string&& newValue);
            const char*        c_str() const;

            bool operator==(const LuaString& other) const;

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            std::string to_string() const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaString>
    {
        size_t operator()(const LuaWrapper::LuaString& luaEntity) const;
    };
}

#endif // LUASTRING_HPP

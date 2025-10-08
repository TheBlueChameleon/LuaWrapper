#ifndef LUASTRING_HPP
#define LUASTRING_HPP

#include <string>

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaString : public LuaEntity
    {
        private:
            std::string value;

        public:
            LuaString();
            LuaString(const char* value);
            LuaString(const std::string& value);
            LuaString(std::string&& value);

            LuaString(const LuaString& other) = default;
            LuaString(LuaString&& other);
            LuaString& operator=(const LuaString& other) = default;
            LuaString& operator=(LuaString&& other);

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            bool isString() const;

            const std::string& getValue() const;
            void        setValue(const std::string& newValue);

            std::string to_string() const;
            const char* c_str() const;

            bool operator==(const LuaString& other) const;
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

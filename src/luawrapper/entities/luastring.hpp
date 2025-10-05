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
            LuaString(const char* value = "");
            LuaString(const std::string& value);
            LuaString(std::string&& value);

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            bool    isString() const;

            std::string getValue() const;
            void        setValue(const std::string& newValue);

            std::string to_string() const;
    };
}

#endif // LUASTRING_HPP

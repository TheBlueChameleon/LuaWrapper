#ifndef LUABOOLEAN_HPP
#define LUABOOLEAN_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaBoolean : public LuaEntity
    {
        private:
            bool value;

        public:
            LuaBoolean(bool value = true);

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);
            void popFromLua(lua_State* L);

            bool isBoolean() const;

            bool getValue() const;
            void setValue(const bool newValue);

            std::string repr() const;
    };
}

#endif // LUABOOLEAN_HPP

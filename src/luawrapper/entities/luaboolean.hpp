#ifndef LUABOOLEAN_HPP
#define LUABOOLEAN_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaBoolean : public LuaEntity
    {
        private:
            bool value;

        protected:
            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);
            void popFromLua(lua_State* L);

        public:
            LuaBoolean(bool value = true);

            static LuaTypeID getStaticTypeId();

            bool isBoolean() const;

            bool get() const;
            void set(const bool newValue);
    };
}

#endif // LUABOOLEAN_HPP

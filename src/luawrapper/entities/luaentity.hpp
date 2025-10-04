#ifndef LUAENTITY_HPP
#define LUAENTITY_HPP

#include "../util/luacapi.hpp"
#include "../util/luatypes.hpp"

namespace LuaWrapper
{
    class LuaNil;
    class LuaBoolean;

    class LuaEntity
    {
        protected:
            const LuaTypeID typeID;

            LuaEntity(const LuaTypeID);

        public:
            virtual void pushToLua(lua_State* L) const = 0;
            virtual void fetchFromLua(lua_State* L) = 0;
            virtual void popFromLua(lua_State* L) = 0;

            LuaTypeID getType() const;

            bool isNil() const;
            bool isBoolean() const;
            bool isLightUserData() const;
            bool isNumber() const;
            bool isString() const;
            bool isTable() const;
            bool isFunction() const;
            bool isThread() const;

            LuaNil& asLuaNil();
            const LuaNil& asLuaNil() const;
    };
}

#endif // LUAENTITY_HPP

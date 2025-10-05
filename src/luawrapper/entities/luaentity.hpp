#ifndef LUAENTITY_HPP
#define LUAENTITY_HPP

#include <string>

#include "../util/luacapi.hpp"
#include "../util/luatypes.hpp"

namespace LuaWrapper
{
    class LuaNil;
    class LuaBoolean;
    class LuaLightUserData;

    class LuaEntity
    {
        protected:
            const LuaTypeId typeId;

            LuaEntity(const LuaTypeId);

        public:
            virtual ~LuaEntity();

            virtual void pushToLua(lua_State* L) const = 0;
            virtual void fetchFromLua(lua_State* L) = 0;
            virtual void popFromLua(lua_State* L);

            LuaTypeId getTypeId() const;
            static LuaTypeId getStaticTypeId();

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
            LuaBoolean& asLuaBoolean();
            const LuaBoolean& asLuaBoolean() const;
            LuaLightUserData& asLuaLightUserData();
            const LuaLightUserData& asLuaLightUserData() const;

            virtual std::string repr() const = 0;
    };
}

#endif // LUAENTITY_HPP

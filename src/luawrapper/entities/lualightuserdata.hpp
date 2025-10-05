#ifndef LUALIGHTUSERDATA_HPP
#define LUALIGHTUSERDATA_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaLightUserData : public LuaEntity
    {
        private:
            const void* value;

        public:
            LuaLightUserData(const void* value = nullptr);

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            bool isLightUserData() const;

            const void* getValue() const;
            void        setValue(const void* newValue);

            std::string repr() const;
    };
}

#endif // LUALIGHTUSERDATA_HPP

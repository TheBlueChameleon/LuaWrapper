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
    class LuaNumber;
    class LuaString;
    class LuaTable;

    class LuaEntity
    {
        protected:
            const LuaTypeId typeId;

            LuaEntity(const LuaTypeId);

        public:
            virtual ~LuaEntity();

            virtual void pushToLua(lua_State* L) const = 0;
            virtual void fetchFromLua(lua_State* L) = 0;
            void popFromLua(lua_State* L);

            LuaTypeId getTypeId() const;
            static LuaTypeId getStaticTypeId();

            virtual bool isNil() const;
            virtual bool isBoolean() const;
            virtual bool isLightUserData() const;
            virtual bool isNumber() const;
            virtual bool isString() const;
            virtual bool isTable() const;
            virtual bool isFunction() const;
            virtual bool isThread() const;

            LuaNil& asLuaNil();
            const LuaNil& asLuaNil() const;
            LuaBoolean& asLuaBoolean();
            const LuaBoolean& asLuaBoolean() const;
            LuaLightUserData& asLuaLightUserData();
            const LuaLightUserData& asLuaLightUserData() const;
            LuaNumber& asLuaNumber();
            const LuaNumber& asLuaNumber() const;
            LuaString& asLuaString();
            const LuaString& asLuaString() const;
            LuaTable& asLuaTable();
            const LuaTable& asLuaTable() const;

            virtual std::string to_string() const = 0;
            virtual size_t getHash() const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaEntity>
    {
        size_t operator()(const LuaWrapper::LuaEntity& luaEntity) const;
    };
}

#endif // LUAENTITY_HPP

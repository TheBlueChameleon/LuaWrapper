#ifndef LUATYPES_H
#define LUATYPES_H

#include <string>
#include <variant>

#include "luacapi.hpp"

namespace LuaWrapper
{
    class LuaTypeId
    {
        public:
            static constexpr auto None = LUA_TNONE;

            static constexpr auto Nil = LUA_TNIL;
            static constexpr auto Boolean = LUA_TBOOLEAN;
            static constexpr auto LightUserData = LUA_TLIGHTUSERDATA;
            static constexpr auto Number = LUA_TNUMBER;
            static constexpr auto String = LUA_TSTRING;
            static constexpr auto Table = LUA_TTABLE;
            static constexpr auto Function= LUA_TFUNCTION;
            static constexpr auto UserData = LUA_TUSERDATA;
            static constexpr auto Thread = LUA_TTHREAD;

            static constexpr auto NumberOfTypes = LUA_NUMTYPES;

        private:
            int typeId;

        public:
            LuaTypeId();
            LuaTypeId(const int typeId);

            std::string getTypeName() const;
            static std::string getTypeName(const int typeId);

            operator int() const;
            bool operator==(const LuaTypeId other) const;
            bool operator==(const int other) const;
    };

    // ====================================================================== //

    // TODO: add lua_CFunction?
    using LuaTrivialVariant = std::variant<nullptr_t, bool, const void*, int, double, char*, std::string>;
    class LuaTrivialType : public LuaTrivialVariant
    {
        public:
            using LuaTrivialVariant::variant;

            static constexpr auto Nil = 0;
            static constexpr auto Boolean = 1;
            static constexpr auto LightUserData = 2;
            static constexpr auto Integer = 3;
            static constexpr auto Double = 4;
            static constexpr auto CharPtr = 5;
            static constexpr auto String = 6;

            std::string         getTrivialTypeName() const;

            nullptr_t           getAsNil() const;
            bool                getAsBoolean() const;
            const void*         getAsLightUserData() const;
            int                 getAsInteger() const;
            double              getAsDouble() const;
            const char*         getAsCharPtr() const;
            const std::string&  getAsString() const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaTypeId>
    {
        size_t operator()(const LuaWrapper::LuaTypeId& typeId) const;
    };
}

#endif // LUATYPES_H

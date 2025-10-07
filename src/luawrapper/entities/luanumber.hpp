#ifndef LUANUMBER_HPP
#define LUANUMBER_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaNumber : public LuaEntity
    {
        private:
            double value;

        public:
            LuaNumber();
            LuaNumber(const double value);

            LuaNumber(const LuaNumber& other) = default;
            LuaNumber(LuaNumber&& other) = default;

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            bool    isNumber() const;

            double  getValue() const;
            void    setValue(double newValue);

            std::string to_string() const;

            bool operator==(const LuaNumber& other) const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaNumber>
    {
        size_t operator()(const LuaWrapper::LuaNumber& luaEntity) const;
    };
}

#endif // LUANUMBER_HPP

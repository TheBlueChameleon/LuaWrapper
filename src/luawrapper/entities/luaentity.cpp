#include <string>
using namespace std::string_literals;

#include "../util/luautil.hpp"

#include "luaentity.hpp"
#include "luaentities.hpp"

namespace LuaWrapper
{
    LuaEntity::LuaEntity(const LuaTypeID typeID) :
        typeID(typeID)
    {}

    LuaTypeID LuaEntity::getType() const
    {
        return typeID;
    }

    bool LuaEntity::isNil() const
    {
        return false;
    }

    bool LuaEntity::isBoolean() const
    {
        return false;
    }

    bool LuaEntity::isLightUserData() const
    {
        return false;
    }

    bool LuaEntity::isNumber() const
    {
        return false;
    }

    bool LuaEntity::isString() const
    {
        return false;
    }

    bool LuaEntity::isTable() const
    {
        return false;
    }

    bool LuaEntity::isFunction() const
    {
        return false;
    }

    bool LuaEntity::isThread() const
    {
        return false;
    }

    template<typename T>
    T& castOrThrow(LuaEntity* ptr)
    {
        T* cast = dynamic_cast<T*>(ptr);
        if (cast == nullptr)
        {
            throw LuaTypeError(
                "Could not convert to "s + getTypeName(ptr->getType()) + " "
                "because entity is a " + getTypeName(ptr->getType())
            );
        }
        else
        {
            return *cast;
        }
    }

    LuaNil& LuaEntity::asLuaNil()
    {
        return dynamic_cast<LuaNil&>(*this);
    }

    const LuaNil& LuaEntity::asLuaNil() const
    {
        return dynamic_cast<const LuaNil&>(*this);
    }
}

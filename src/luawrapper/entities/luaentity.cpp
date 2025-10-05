#include <string>
using namespace std::string_literals;

#include "../util/luautil.hpp"

#include "concepts.hpp"
#include "luaentity.hpp"
#include "entities.hpp"

namespace LuaWrapper
{
    LuaEntity::LuaEntity(const LuaTypeId typeID) :
        typeId(typeID)
    {}

    LuaEntity::~LuaEntity()
    {}

    void LuaEntity::popFromLua(lua_State* L)
    {
        fetchFromLua(L);
        lua_pop(L, 1);
    }

    LuaTypeId LuaEntity::getTypeId() const
    {
        return typeId;
    }

    LuaTypeId LuaEntity::getStaticTypeId()
    {
        return LuaTypeId::None;
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

    template<IHasStaticTypeId T>
    T& castOrThrow(LuaEntity* ptr)
    {
        T* cast = dynamic_cast<T*>(ptr);
        if (cast == nullptr)
        {
            throw LuaTypeError(
                "Could not convert to "s + T::getStaticTypeId().getTypeName() + " "
                "because entity is a " + ptr->getTypeId().getTypeName()
            );
        }
        else
        {
            return *cast;
        }
    }

    template<IHasStaticTypeId T>
    const T& castOrThrow(const LuaEntity* ptr)
    {
        const T* cast = dynamic_cast<const T*>(ptr);
        if (cast == nullptr)
        {
            throw LuaTypeError(
                "Could not convert to "s + T::getStaticTypeId().getTypeName() + " "
                "because entity is a " + ptr->getTypeId().getTypeName()
            );
        }
        else
        {
            return *cast;
        }
    }

    LuaNil& LuaEntity::asLuaNil()
    {
        return castOrThrow<LuaNil>(this);
    }

    const LuaNil& LuaEntity::asLuaNil() const
    {
        return castOrThrow<const LuaNil>(this);
    }

    LuaBoolean& LuaEntity::asLuaBoolean()
    {
        return castOrThrow<LuaBoolean>(this);
    }

    const LuaBoolean& LuaEntity::asLuaBoolean() const
    {
        return castOrThrow<const LuaBoolean>(this);
    }

    LuaLightUserData& LuaEntity::asLuaLightUserData()
    {
        return castOrThrow<LuaLightUserData>(this);
    }

    const LuaLightUserData& LuaEntity::asLuaLightUserData() const
    {
        return castOrThrow<const LuaLightUserData>(this);
    }
}

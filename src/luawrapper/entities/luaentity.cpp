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

    LuaNumber& LuaEntity::asLuaNumber()
    {
        return castOrThrow<LuaNumber>(this);
    }

    const LuaNumber& LuaEntity::asLuaNumber() const
    {
        return castOrThrow<const LuaNumber>(this);
    }

    LuaString& LuaEntity::asLuaString()
    {
        return castOrThrow<LuaString>(this);
    }

    const LuaString& LuaEntity::asLuaString() const
    {
        return castOrThrow<const LuaString>(this);
    }

    LuaTable& LuaEntity::asLuaTable()
    {
        return castOrThrow<LuaTable>(this);
    }

    const LuaTable& LuaEntity::asLuaTable() const
    {
        return castOrThrow<const LuaTable>(this);
    }

    size_t LuaEntity::getHash() const
    {
        return std::hash<LuaWrapper::LuaEntity>()(*this);
    }

    bool LuaEntity::operator==(const LuaEntity& other) const
    {
        if (typeId != other.typeId)
        {
            return false;
        }

        switch (getTypeId())
        {
            case LuaWrapper::LuaTypeId::None:
                return false;
            case LuaWrapper::LuaTypeId::Nil:
                return true;
            case LuaWrapper::LuaTypeId::Boolean:
                return asLuaBoolean() == other.asLuaBoolean();
            case LuaWrapper::LuaTypeId::LightUserData:
                return asLuaLightUserData() == other.asLuaLightUserData();
            case LuaWrapper::LuaTypeId::Number:
                return asLuaNumber() == other.asLuaNumber();
            case LuaWrapper::LuaTypeId::String:
                return asLuaString() == other.asLuaString();
            case LuaWrapper::LuaTypeId::Table:
                return asLuaTable() == other.asLuaTable();
            case LuaWrapper::LuaTypeId::Function:
            case LuaWrapper::LuaTypeId::UserData:
            case LuaWrapper::LuaTypeId::Thread:
                throw LuaWrapper::LuaNotImplementedError(
                    "Not yet implemented: compare equal for "s + getTypeId().getTypeName()
                );

            default:
                throw LuaWrapper::LuaInvalidArgumentError(
                    "Cannot compare equal for Lua entity with type id "s + std::to_string(getTypeId())
                );
        }


        return true;
    }
}

namespace std
{
    size_t std::hash<LuaWrapper::LuaEntity>::operator()(const LuaWrapper::LuaEntity& luaEntity) const
    {
        switch (luaEntity.getTypeId())
        {
            case LuaWrapper::LuaTypeId::None:
                return -1;
            case LuaWrapper::LuaTypeId::Nil:
                return std::hash<LuaWrapper::LuaNil>()(luaEntity.asLuaNil());
            case LuaWrapper::LuaTypeId::Boolean:
                return std::hash<LuaWrapper::LuaBoolean>()(luaEntity.asLuaBoolean());
            case LuaWrapper::LuaTypeId::LightUserData:
                return std::hash<LuaWrapper::LuaLightUserData>()(luaEntity.asLuaLightUserData());
            case LuaWrapper::LuaTypeId::Number:
                return std::hash<LuaWrapper::LuaNumber>()(luaEntity.asLuaNumber());
            case LuaWrapper::LuaTypeId::String:
                return std::hash<LuaWrapper::LuaString>()(luaEntity.asLuaString());
            case LuaWrapper::LuaTypeId::Table:
                return std::hash<LuaWrapper::LuaTable>()(luaEntity.asLuaTable());
            case LuaWrapper::LuaTypeId::Function:
            case LuaWrapper::LuaTypeId::UserData:
            case LuaWrapper::LuaTypeId::Thread:
                throw LuaWrapper::LuaNotImplementedError(
                    "Not yet implemented: hash for "s + luaEntity.getTypeId().getTypeName()
                );

            default:
                throw LuaWrapper::LuaInvalidArgumentError(
                    "Cannot compute hash for Lua entity with type id "s + std::to_string(luaEntity.getTypeId())
                );
        }
    }
}

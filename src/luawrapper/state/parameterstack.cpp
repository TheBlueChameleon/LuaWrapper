#include <string>
using namespace std::string_literals;

#include "parameterstack.hpp"
#include "../entities/entities.hpp"
#include "../util/luaerror.hpp"

namespace LuaWrapper
{
    ParameterStack::ParameterStack()
    {}

    ParameterStack::ParameterStack(const LuaWrappableType& item)
    {}

    ParameterStack::ParameterStack(const std::initializer_list<LuaWrappableType>& items)
    {
        for (const auto& item : items)
        {
            entities.push_back(LuaEntityFactory::makeLuaEntity(item));
        }
    }

    ParameterStack::~ParameterStack()
    {
        for (auto* ptr : entities)
        {
            delete ptr;
        }
    }

    void ParameterStack::pushToLua(lua_State* L) const
    {
        for (const auto* param: entities)
        {
            param->pushToLua(L);
        }
    }

    void ParameterStack::popFromLua(lua_State* L, int nArgs)
    {
        nArgs = ((nArgs == -1) ? lua_gettop(L) : nArgs);
        while (lua_gettop(L))
        {
            if (nArgs == 0)
            {
                break;
            }

            entities.push_front(LuaEntityFactory::makeLuaEntityFromTypeId(lua_type(L, -1)));
            entities.front()->popFromLua(L);

            --nArgs;
        }
    }

    ParameterStack& ParameterStack::addEntity(const LuaEntity& entity)
    {
        entities.push_back(LuaEntityFactory::makeLuaEntity(entity));
        return *this;
    }

    ParameterStack& ParameterStack::addEntity(LuaEntity&& entity)
    {
        entities.push_back(LuaEntityFactory::makeLuaEntity(std::move(entity)));
        return *this;
    }

    ParameterStack& ParameterStack::addEntity(const LuaWrappableType& wrappable)
    {
        entities.push_back(LuaEntityFactory::makeLuaEntity(wrappable));
        return *this;
    }

    ParameterStack& ParameterStack::addEntity(LuaWrappableType&& wrappable)
    {
        entities.push_back(LuaEntityFactory::makeLuaEntity(std::move(wrappable)));
        return *this;
    }

    size_t ParameterStack::size() const
    {
        return entities.size();
    }

    bool ParameterStack::empty() const
    {
        return entities.empty();
    }

    ParameterStack::value_type ParameterStack::at(size_t index) const
    {
        if (index >= size())
        {
            throw LuaInvalidArgumentError(
                "Invalid index '"s + std::to_string(index) + "': "
                "ParameterStack has only " + std::to_string(size()) + " elements."
            );
        }
        return entities[index];
    }

    ParameterStack::iterator ParameterStack::begin()
    {
        return entities.begin();
    }

    ParameterStack::const_iterator ParameterStack::begin() const
    {
        return entities.cbegin();
    }

    ParameterStack::iterator ParameterStack::end()
    {
        return entities.end();
    }

    ParameterStack::const_iterator ParameterStack::end() const
    {
        return entities.cend();
    }
}

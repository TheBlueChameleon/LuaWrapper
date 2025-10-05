#include <iostream>

#include "parameterstack.hpp"
#include "../entities/entities.hpp"

namespace LuaWrapper
{
    ParameterStack::ParameterStack()
    {}

    ParameterStack::ParameterStack(const LuaTrivialType& item)
    {}

    ParameterStack::ParameterStack(const std::initializer_list<LuaTrivialType>& items)
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

    // ParameterStack& ParameterStack::withNil()
    // {
    //     auto n = LuaNil();
    //     push_back(n);
    //     return *this;
    // }

    // ParameterStack& ParameterStack::withBoolean(const LuaBoolean& value)
    // {
    //     push_back(std::ref(value));
    //     return *this;
    // }
}

#ifndef PARAMETERSTACK_HPP
#define PARAMETERSTACK_HPP

#include <deque>

#include "../util/luacapi.hpp"
#include "../entities/entities.hpp"

namespace LuaWrapper
{
    class LuaEntity;

    class ParameterStack
    {
        public:
            using container                 = std::deque<LuaEntity*>;

            using iterator                  = container::iterator;
            using const_iterator            = container::const_iterator;

            using reverse_iterator          = container::reverse_iterator;
            using const_reverse_iterator    = container::const_reverse_iterator;

            using difference_type           = container::difference_type;
            using value_type                = container::value_type;
            using pointer                   = container::pointer;
            using reference                 = container::reference;
            using iterator_category         = iterator::iterator_category;

        private:
            std::deque<LuaEntity*> entities;

        public:
            ParameterStack();
            ParameterStack(const LuaTrivialType& item);
            ParameterStack(const std::initializer_list<LuaTrivialType>& items);
            ~ParameterStack();

            void pushToLua(lua_State* L) const;
            void popFromLua(lua_State* L, int nArgs = -1);       // todo

            ParameterStack& addEntity(const LuaEntity& entity);
            ParameterStack& addEntity(LuaEntity&& entity);
            ParameterStack& addEntity(const LuaTrivialType& trivialEntity);
            ParameterStack& addEntity(LuaTrivialType&& trivialEntity);

            size_t          size() const;
            bool            empty() const;
            value_type      at(size_t index) const;

            iterator        begin();
            const_iterator  begin() const;
            iterator        end();
            const_iterator  end() const;
    };
}

#endif // PARAMETERSTACK_HPP

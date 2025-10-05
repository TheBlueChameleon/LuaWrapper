#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <concepts>

namespace LuaWrapper
{
    template<typename T>
    concept IHasStaticTypeId = requires(T v)
    {
        {
            T::getStaticTypeId()
        }
        -> std::convertible_to<LuaTypeId>;
    };
}

#endif // CONCEPTS_HPP

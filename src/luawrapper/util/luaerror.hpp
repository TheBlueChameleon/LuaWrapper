#ifndef LUAERROR_HPP
#define LUAERROR_HPP

#include <stdexcept>

namespace LuaWrapper
{
    class LuaError : public std::runtime_error
    {
        public:
            using std::runtime_error::runtime_error;
    };

    class LuaInitError : public LuaError
    {
        public:
            using LuaError::LuaError;
    };

    class LuaTypeError : public LuaError
    {
        public:
            using LuaError::LuaError;
    };

    class LuaInvalidArgumentError : public LuaError
    {
        public:
            using LuaError::LuaError;
    };

    class LuaInvalidStateError : public LuaError
    {
        public:
            using LuaError::LuaError;
    };

    class LuaNotImplementedError : public LuaError
    {
        public:
            using LuaError::LuaError;
    };
}

#endif // LUAERROR_HPP

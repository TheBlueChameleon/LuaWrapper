#include "commonconversionutil.hpp"

#include <luawrapper.hpp>

int funcPtr(lua_State*)
{
    return 1;
}

void* getVoidPtr()
{
    return reinterpret_cast<void*>(funcPtr);
}

const void* exposeCString(const LuaWrapper::LuaString& luaString)
{
    return reinterpret_cast<const void*>(luaString.c_str());
}

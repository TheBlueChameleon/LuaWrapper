#ifndef COMMONCONVERSIONUTIL_HPP
#define COMMONCONVERSIONUTIL_HPP

#include "util/luacapi.hpp"
#include "entities/luaentityforwarddeclarations.hpp"

int funcPtr(lua_State*);

void* getVoidPtr();

const void* exposeCString(const LuaWrapper::LuaString& luaString);

#endif // COMMONCONVERSIONUTIL_HPP

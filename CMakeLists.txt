cmake_minimum_required(VERSION 3.16)

include(FetchContent)
include(CMakePrintHelpers)
include(GNUInstallDirs)

# ============================================================================ #
# language definition

project(LuaWrapper
    LANGUAGES CXX
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================ #
# external dependencies

FetchContent_Declare(
    lua
    GIT_REPOSITORY "https://github.com/marovira/lua"
    GIT_TAG "5.4.8"
)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG        "v1.17.0"
)
# more `FetchContent_Declare`s (if any). They should all be declared
# before any calls to FetchContent_Make_available (see docs for why).
FetchContent_MakeAvailable(lua)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# more `FetchContent_MakeAvailable`s (if any).

# ============================================================================ #
# source file definitions

include_directories(
    src/
    src/luawrapper/
    "${lua_SOURCE_DIR}/src"
)

# ............................................................................ #
# lib

add_library(LuaWrapper-Lib STATIC
    src/luawrapper/luawrapper.hpp

    src/luawrapper/util/luautil.hpp
    src/luawrapper/util/luacapi.hpp
    src/luawrapper/util/luatypes.hpp                src/luawrapper/util/luatypes.cpp
    src/luawrapper/util/luaerror.hpp                src/luawrapper/util/luaerror.cpp

    src/luawrapper/entities/entities.hpp
    src/luawrapper/entities/concepts.hpp
    src/luawrapper/entities/luaentity.hpp           src/luawrapper/entities/luaentity.cpp
    src/luawrapper/entities/luaentityfactory.hpp    src/luawrapper/entities/luaentityfactory.cpp
    src/luawrapper/entities/luanil.hpp              src/luawrapper/entities/luanil.cpp
    src/luawrapper/entities/luaboolean.hpp          src/luawrapper/entities/luaboolean.cpp
    src/luawrapper/entities/lualightuserdata.hpp    src/luawrapper/entities/lualightuserdata.cpp
    src/luawrapper/entities/luanumber.hpp           src/luawrapper/entities/luanumber.cpp
    src/luawrapper/entities/luastring.hpp           src/luawrapper/entities/luastring.cpp
    src/luawrapper/entities/luatable.hpp            src/luawrapper/entities/luatable.cpp

    src/luawrapper/state/state.hpp
    src/luawrapper/state/luastate.hpp               src/luawrapper/state/luastate.cpp
    src/luawrapper/state/parameterstack.hpp         src/luawrapper/state/parameterstack.cpp

)

target_link_libraries(LuaWrapper-Lib PUBLIC
    lua::lua
)

# ............................................................................ #
# tests

include(GoogleTest)

add_executable(LuaWrapper-Test
    src/test/main.cpp
    src/test/typesystemtest.cpp
    src/test/statetest.cpp


)

target_link_libraries(LuaWrapper-Test
    LuaWrapper-Lib
    GTest::gtest_main
)

gtest_discover_tests(LuaWrapper-Test)

# ============================================================================ #

install(TARGETS LuaWrapper-Lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

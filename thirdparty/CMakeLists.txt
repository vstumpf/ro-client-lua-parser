### lua
add_library(lua
  lua-5.1.5/src/lapi.c
  lua-5.1.5/src/ldebug.c
  lua-5.1.5/src/linit.c
  lua-5.1.5/src/loadlib.c
  lua-5.1.5/src/lstate.c
  lua-5.1.5/src/ltm.c
  lua-5.1.5/src/lzio.c
  lua-5.1.5/src/lauxlib.c
  lua-5.1.5/src/ldo.c
  lua-5.1.5/src/liolib.c
  lua-5.1.5/src/lobject.c
  lua-5.1.5/src/lstring.c
  lua-5.1.5/src/lua.c
  lua-5.1.5/src/print.c
  lua-5.1.5/src/lbaselib.c
  lua-5.1.5/src/ldump.c
  lua-5.1.5/src/llex.c
  lua-5.1.5/src/lopcodes.c
  lua-5.1.5/src/lstrlib.c
  lua-5.1.5/src/luac.c
  lua-5.1.5/src/lcode.c
  lua-5.1.5/src/lfunc.c
  lua-5.1.5/src/lmathlib.c
  lua-5.1.5/src/loslib.c
  lua-5.1.5/src/ltable.c
  lua-5.1.5/src/lundump.c
  lua-5.1.5/src/ldblib.c
  lua-5.1.5/src/lgc.c
  lua-5.1.5/src/lmem.c
  lua-5.1.5/src/lparser.c
  lua-5.1.5/src/ltablib.c
  lua-5.1.5/src/lvm.c
)
add_library(lua::lua ALIAS lua)

if (WIN32)
  target_compile_definitions(lua PRIVATE LUA_USE_WINDOWS)
endif()

target_include_directories(lua PUBLIC lua-5.1.5/src)
if (UNIX)
  target_compile_definitions(lua PRIVATE LUA_USE_LINUX)
  find_package(Readline REQUIRED)
  target_link_libraries(lua PRIVATE dl ${Readline_LIBRARY})
  target_include_directories(lua PUBLIC ${Readline_INCLUDE_DIR})
endif()

### sol2
set(SOL2_LUA_VERSION "5.1.5" CACHE STRING "The version of Lua used")
# we build Lua manually
set(SOL2_BUILD_LUA FALSE CACHE BOOL "Always build Lua, do not search for it in the system")
add_subdirectory(sol2)

add_library(cxxopts INTERFACE)
target_include_directories(cxxopts INTERFACE cxxopts/include)
add_library(cxxopts::cxxopts ALIAS cxxopts)

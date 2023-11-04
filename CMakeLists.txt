cmake_minimum_required(VERSION 3.16)
project(ro-client-lua-parser VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CXX_STANDARD 20)

add_subdirectory(thirdparty)
add_subdirectory(src)


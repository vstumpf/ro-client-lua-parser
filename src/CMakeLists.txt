add_executable(ro-client-lua-parser
  main.cpp
  args.cpp
  codec.cpp
)

target_link_libraries(ro-client-lua-parser PRIVATE
  lua::lua
  sol2::sol2
  cxxopts::cxxopts
  nlohmann_json::nlohmann_json
)

set_property(TARGET ro-client-lua-parser PROPERTY CXX_STANDARD 17)

add_contract(hello hello ${CMAKE_CURRENT_SOURCE_DIR}/src/hello.cpp)
target_include_directories(hello.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(hello.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

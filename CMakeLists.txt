cmake_minimum_required(VERSION 3.20)

project(Orbit CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM 12 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_executable(orbit
    src/orbit.cpp
    src/lexer.cpp
    src/parser.cpp
    src/codegen.cpp
)

target_include_directories(orbit PRIVATE ${LLVM_INCLUDE_DIRS})

target_link_libraries(orbit PRIVATE
    LLVM::Core
    LLVM::IR
    LLVM::Support
)

install(TARGETS orbit RUNTIME DESTINATION bin)

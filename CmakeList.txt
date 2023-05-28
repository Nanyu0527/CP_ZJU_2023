cmake_minimum_required(VERSION 3.16)
project(Compiler)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
add_executable(Compiler ./src/CodeGenerator.cpp ./src/CodeGenerator.h ./src/AST.cpp ./src/AST.h ./src/main.cpp ./src/lab3_yacc.cpp ./src/lab3_yacc.hpp ./src/lex.yy.cc)
set(LLVM_LINK_COMPONENTS
    Core
    ExecutionEngine
    Interpreter
    MC
    Support
    nativecodegen
    mcjit
    asmparser
    x86asmparser
)
llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})
target_link_libraries(Compiler ${llvm_libs})
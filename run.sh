#!/bin/bash
make
./Compiler
cd test
llvm-as test.ll -o test.bc
clang test.bc -o out
./out
cd ..
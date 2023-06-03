#!/bin/bash
make
./Compiler
cd test
llvm-as test2.c -o test.bc
clang test.bc -o out
./out
cd ..
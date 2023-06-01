test:
	flex -o lex.yy.cc c.l
	bison -d -o lab_yacc.cpp c.y
	gcc lex.yy.cc lab_yacc.cpp -o test `llvm-config --cxxflags`
test:
	flex -o lex.yy.cc c.l
	bison -d -o lab_yacc.cpp c.y
	# gcc -o test lex.yy.cc lab_yacc.cpp `llvm-config --cxxflags`
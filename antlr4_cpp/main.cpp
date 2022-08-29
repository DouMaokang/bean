#include <iostream>
#include "antlr4-runtime.h"
#include "HelloLexer.h"
#include "HelloParser.h"


int main() {
	std::ifstream stream;
	stream.open("/Users/maokang/CLionProjects/bean/antlr4_cpp/input.txt");

	antlr4::ANTLRInputStream input(stream);
	antlrcpptest::HelloLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	antlrcpptest::HelloParser parser(&tokens);
	auto tree = parser.r();
	std::cout << tree->toStringTree(&parser) << std::endl;
	std::cout << tree->toString() << std::endl;
	return 0;
}
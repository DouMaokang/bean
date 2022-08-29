//
// Created by Maokang Dou on 29/8/22.
//

#include <iostream>
#include "antlr4-runtime.h"
#include "ArrayInitParser.h"
#include "ArrayInitLexer.h"
#include "ArrayInitBaseListener.h"

class TreeShapeListener : public arrayinit::ArrayInitBaseListener {
public:
	void enterInit(arrayinit::ArrayInitParser::InitContext *ctx) override {
		std::cout << "\"";
	}

	void exitInit(arrayinit::ArrayInitParser::InitContext *ctx) override {
		std::cout << "\"";
	}

	void enterValue(arrayinit::ArrayInitParser::ValueContext *ctx) override {
		// Assumes no nested array initializers
		int value = std::stoi(ctx->INT()->getText());
		std::cout << value;
	}
};

int main() {
	std::ifstream stream;
	stream.open("/Users/maokang/CLionProjects/bean/antlr4_cpp/array_init/input.txt");

	antlr4::ANTLRInputStream input(stream);
	arrayinit::ArrayInitLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	arrayinit::ArrayInitParser parser(&tokens);
	antlr4::tree::ParseTree *tree = parser.init();

	std::cout << tree->toStringTree(&parser) << std::endl;

	TreeShapeListener listener;
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
}
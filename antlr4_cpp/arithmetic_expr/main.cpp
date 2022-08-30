//
// Created by Maokang Dou on 30/8/22.
//

#include <iostream>
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseVisitor.h"
#include "unordered_map"

class EvalVisitor : public expr::ExprBaseVisitor {
public:
	std::unordered_map<std::string, int> memory;

	std::any visitAssign(expr::ExprParser::AssignContext *ctx) override {
		std::string id = ctx->ID()->getText();
		int value = std::any_cast<int>(this->visit(ctx->expr()));
		memory[id] = value;
		return value;
	}
	std::any visitPrintExpr(expr::ExprParser::PrintExprContext *ctx) override {
//		std::any value = this->visitChildren(ctx);  // FIXME: does not work?
		std::any value = this->visit(ctx->expr());
		std::cout << std::any_cast<int>(value) << std::endl;
		return 0;
	}
	std::any visitParens(expr::ExprParser::ParensContext *ctx) override {
		return this->visit(ctx->expr());
	}
	std::any visitMulDiv(expr::ExprParser::MulDivContext *ctx) override {
		int left = std::any_cast<int>(this->visit(ctx->expr(0)));
		int right = std::any_cast<int>(this->visit(ctx->expr(1)));
		if (ctx->MUL()) {
			// if the expr is multiplication
			return left * right;
		}
		return left / right;

	}
	std::any visitAddSub(expr::ExprParser::AddSubContext *ctx) override {
		int left = std::any_cast<int>(this->visit(ctx->expr(0)));
		int right = std::any_cast<int>(this->visit(ctx->expr(1)));
		if (ctx->ADD()) {
			return left + right;
		}
		return left - right;
	}
	std::any visitId(expr::ExprParser::IdContext *ctx) override {
		std::string id = ctx->ID()->getText();
		if (memory.find(id) != memory.end()) {
			return memory[id];
		}
		return 0;
	}
	std::any visitInt(expr::ExprParser::IntContext *ctx) override {
		int value = std::stoi(ctx->INT()->getText());
		return value;
	}
};


int main(int argv, char** args) {
	std::ifstream stream;
	stream.open("/Users/maokang/CLionProjects/bean/antlr4_cpp/arithmetic_expr/input.txt");

	antlr4::ANTLRInputStream input(stream);
	expr::ExprLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	expr::ExprParser parser(&tokens);
	antlr4::tree::ParseTree *tree = parser.prog();

	// visitor
	EvalVisitor visitor;
	visitor.visit(tree);

	return 0;
}
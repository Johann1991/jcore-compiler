#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include <vector>
#include <memory>

// Forward declaration of abstract syntax tree (AST) classes
class Expression;
class BinaryExpression;
class NumberExpression;

// Parser class declaration
class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<Expression> parseExpression();

private:
    std::vector<Token> tokens;
    size_t currentIndex;

    Token currentToken();
    void advance();
    std::unique_ptr<Expression> parseAddition();
    std::unique_ptr<Expression> parseTerm();
    std::unique_ptr<Expression> parseFactor();
};

// AST classes
class Expression {
public:
    virtual ~Expression() {}
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(Token op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
    const Token& getOp() const;
    const Expression* getLeft() const;
    const Expression* getRight() const;

private:
    Token op;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

class NumberExpression : public Expression {
public:
    NumberExpression(int value);
    int getValue() const;

private:
    int value;
};

#endif // PARSER_H
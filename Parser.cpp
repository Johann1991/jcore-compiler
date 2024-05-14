#include "Parser.h"
#include <stdexcept>  // Include this to use std::runtime_error


// Parser constructor
Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), currentIndex(0) {}

// Method to parse the whole expression
std::unique_ptr<Expression> Parser::parseExpression() {
    return parseAddition();
}

// Method to parse additions and subtractions
std::unique_ptr<Expression> Parser::parseAddition() {
    auto left = parseTerm();
    while (currentToken().type == TokenType::Plus || currentToken().type == TokenType::Minus) {
        Token op = currentToken();
        advance();
        auto right = parseTerm();
        left = std::make_unique<BinaryExpression>(op, std::move(left), std::move(right));
    }
    return left;
}

// Method to parse multiplication and division
std::unique_ptr<Expression> Parser::parseTerm() {
    auto left = parseFactor();
    while (currentToken().type == TokenType::Multiply || 
           currentToken().type == TokenType::Divide ||
           currentToken().type == TokenType::Modulus) {
        Token op = currentToken();
        advance();  // Move past the operator
        auto right = parseFactor();
        left = std::make_unique<BinaryExpression>(op, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expression> Parser::parseFactor() {
    if (currentToken().type == TokenType::Number) {
        int value = std::stoi(currentToken().text);
        advance();
        return std::make_unique<NumberExpression>(value);
    }
    else if (currentToken().type == TokenType::LeftParen) {
        advance(); // Skip the '('
        auto expr = parseExpression(); // Recursively parse the expression inside the parentheses
        if (currentToken().type == TokenType::RightParen) {
            advance(); // Skip the ')'
            return expr; // Return the parsed expression
        } else {
            throw std::runtime_error("Missing closing parenthesis");
        }
    }
    return nullptr;
}


// Method to get the current token
Token Parser::currentToken() {
    if (currentIndex < tokens.size()) {
        return tokens[currentIndex];
    } else {
        return Token{TokenType::EndOfFile, ""};
    }
}

// Method to advance to the next token
void Parser::advance() {
    if (currentIndex < tokens.size()) {
        currentIndex++;
    }
}

// BinaryExpression constructor and accessors
BinaryExpression::BinaryExpression(Token op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

const Token& BinaryExpression::getOp() const { return op; }
const Expression* BinaryExpression::getLeft() const { return left.get(); }
const Expression* BinaryExpression::getRight() const { return right.get(); }

// NumberExpression constructor and accessor
NumberExpression::NumberExpression(int value) : value(value) {}
int NumberExpression::getValue() const { return value; }

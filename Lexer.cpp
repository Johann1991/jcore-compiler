#include "Lexer.h"

Token Lexer::getNextToken() {
    while (currentChar() != '\0') {
        if (isspace(currentChar())) {
            advance(); // Skip whitespace
        } else if (isdigit(currentChar())) {
            std::string num;
            while (isdigit(currentChar())) {
                num += currentChar();
                advance();
            }
            return Token{TokenType::Number, num};
        } else if (isalpha(currentChar())) {
            std::string id;
            while (isalpha(currentChar())) {
                id += currentChar();
                advance();
            }
            return Token{TokenType::Identifier, id};
        } else {
            switch (currentChar()) {
                case '+':
                    advance();
                    return Token{TokenType::Plus, "+"};
                case '-':
                    advance();
                    return Token{TokenType::Minus, "-"};
                case '*':
                    advance();
                    return Token{TokenType::Multiply, "*"};
                case '/':
                    advance();
                    return Token{TokenType::Divide, "/"};
                case '(':
                    advance();
                    return Token{TokenType::LeftParen, "("};
                case ')':
                    advance();
                    return Token{TokenType::RightParen, ")"};
                default:
                    // Handle unknown characters
                    std::string unknown(1, currentChar());
                    advance();
                    return Token{TokenType::Unknown, std::string(1, currentChar())}; 
            }
        }
    }

    return Token{TokenType::EndOfFile, ""}; // Return EOF when no more characters
}

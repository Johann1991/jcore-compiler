#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <cctype>

// Token types
enum class TokenType {
    Number, Identifier, Plus, Minus, Multiply, Divide, Modulus, LeftParen, RightParen, EndOfFile, Unknown
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
public:
    Lexer(const std::string& source) : source(source), currentIndex(0) {}
    Token getNextToken();

private:
    std::string source;
    size_t currentIndex;

    char currentChar() {
        return currentIndex < source.length() ? source[currentIndex] : '\0'; // Return '\0' at end of source
    }

    void advance() {
        currentIndex++;
    }
};

#endif // LEXER_H

#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <memory>
#include <stdexcept>  // For handling exceptions

// Function to print the AST
void printExpression(const Expression* expr);

int main() {
    std::string input;
    std::cout << "Enter expressions to parse or type 'exit' to quit:\n";

    while (true) {
        std::cout << "> ";
        getline(std::cin, input);  // Read a line from standard input
        if (input == "exit") {
            break;  // Exit the loop if the user types 'exit'
        }

        Lexer lexer(input);
        std::vector<Token> tokens;

        // Tokenize the input
        Token token;
        try {
            do {
                token = lexer.getNextToken();
                tokens.push_back(token);
                std::cout << "Token: " << token.text << ", Type: " << static_cast<int>(token.type) << std::endl;
            } while (token.type != TokenType::EndOfFile);

            // Parse the tokens
            Parser parser(tokens);
            auto expression = parser.parseExpression();

            // Print the AST
            printExpression(expression.get());
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;  // Print error message if an exception occurs
        }
    }

    return 0;
}

void printExpression(const Expression* expr) {
    if (!expr) {
        std::cout << "Invalid expression.\n";
        return;
    }
    if (const NumberExpression* numExpr = dynamic_cast<const NumberExpression*>(expr)) {
        std::cout << "Number: " << numExpr->getValue() << std::endl;
    } else if (const BinaryExpression* binExpr = dynamic_cast<const BinaryExpression*>(expr)) {
        std::cout << "(";
        printExpression(binExpr->getLeft());
        std::cout << " " << binExpr->getOp().text << " ";
        printExpression(binExpr->getRight());
        std::cout << ")";
    }
}

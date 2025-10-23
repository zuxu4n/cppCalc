#include <iostream>
#include <string>
#include <cctype>

bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    std::size_t i = 0;
    if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') {
        if (s.size() == 1) return false; // sign alone is not a number
        i = 1;
    }
    for (; i < s.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

bool isSymbol(const std::string& s) {
    return s.size() == 1 &&
        (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/');
}

double calculate(double left, char op, double right) {
    if (op == '+') return left + right;
    if (op == '-') return left - right;
    if (op == '*') return left * right;
    if (op == '/') return left / right;
    return left; // fallback, should not happen if validated
}

int main() {
    std::cout << "Hello and welcome to Calculator!\n";

    std::string input;
    bool needNum = true;       // true: expect a number, false: expect an operator
    bool hasResult = false;    // tracks if we already have an accumulated result
    char symbol = '+';         // current operator to apply
    double result = 0;

    do {
        if (needNum) {
            std::cout << "Please input a number, or press [ENTER] to complete calculation:\n";
            std::getline(std::cin, input);
            if (input.empty()) break;

            if (isNumber(input)) {
                double value = std::stoi(input);
                if (!hasResult) {
                    result = value;
                    hasResult = true;
                } else {
                    result = calculate(result, symbol, value);
                }
                needNum = false; // next we want an operator
            } else {
                std::cout << input << " is not a number.\n";
            }
        } else {
            std::cout << "Please input a symbol (+ - * /), or press [ENTER] to complete calculation:\n";
            std::getline(std::cin, input);
            if (input.empty()) break;

            if (isSymbol(input)) {
                symbol = input[0];
                needNum = true; // next we want a number
            } else {
                std::cout << input << " is not a valid symbol.\n";
            }
        }
    } while (true);

    if (hasResult) {
        std::cout << "Result: " << result << "\n";
    } else {
        std::cout << "No calculation performed.\n";
    }

    return 0;
}

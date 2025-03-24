#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

class Compiler {
private:
    string expression;
    size_t index;

    char peek() {
        return (index < expression.size()) ? expression[index] : '\0';
    }

    char get() {
        return (index < expression.size()) ? expression[index++] : '\0';
    }

    double number() {
        double result;
        stringstream ss;
        while (isdigit(peek()) || peek() == '.') {
            ss << get();
        }
        ss >> result;
        return result;
    }

    double factor() {
        if (peek() == '(') {
            get();
            double result = expression_();
            get(); // Consume ')'
            return result;
        } else {
            return number();
        }
    }

    double term() {
        double result = factor();
        while (peek() == '*' || peek() == '/') {
            char op = get();
            if (op == '*') result *= factor();
            else result /= factor();
        }
        return result;
    }

    double expression_() {
        double result = term();
        while (peek() == '+' || peek() == '-') {
            char op = get();
            if (op == '+') result += term();
            else result -= term();
        }
        return result;
    }

public:
    Compiler(const string& expr) : expression(expr), index(0) {}

    double evaluate() {
        return expression_();
    }
};

int main() {
    string input;
    cout << "Enter arithmetic expression: ";
    getline(cin, input);
    
    Compiler compiler(input);
    cout << "Result: " << compiler.evaluate() << endl;
    return 0;
}
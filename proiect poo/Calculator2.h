#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

class Calculator {
private:
    static const int MAX_EXPRESSION_LENGTH = 100;
    double outputQueue[MAX_EXPRESSION_LENGTH];
    char operatorStack[MAX_EXPRESSION_LENGTH];
    int outputQueueIndex;
    int operatorStackIndex;

    double add(double a, double b) {
        return a + b;
    }

    double subtract(double a, double b) {
        return a - b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double divide(double a, double b) {
        if (b == 0) {
            throw std::invalid_argument("Impartirea la zero este imposibila");
        }
        return a / b;
    }

    double exponentiate(double a, double b) {
        return std::pow(a, b);
    }

    double nthRoot(double a, double n) {
        if (a < 0 && fmod(n, 2) == 0) {
            throw std::invalid_argument(" eroare extragere radical din numar negativ ");
        }
        return std::pow(a, 1.0 / n);
    }

public:
    Calculator() : outputQueueIndex(0), operatorStackIndex(0) {}

    double evaluate(std::string expression) {
        outputQueueIndex = 0;
        operatorStackIndex = 0;

        for (int i = 0; i < expression.length(); i++) {
            if (expression[i] == ' ') {
                continue;
            }
            else if (isdigit(expression[i])) {
                std::string token;
                while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                    token += expression[i];
                    i++;
                }
                i--;
                outputQueue[outputQueueIndex++] = stod(token);
            }
            else if (expression[i] == '+' || expression[i] == '-') {
                while (operatorStackIndex > 0 &&
                    (operatorStack[operatorStackIndex - 1] == '+' ||
                        operatorStack[operatorStackIndex - 1] == '-' ||
                        operatorStack[operatorStackIndex - 1] == '*' ||
                        operatorStack[operatorStackIndex - 1] == '/' ||
                        operatorStack[operatorStackIndex - 1] == '^' ||
                        operatorStack[operatorStackIndex - 1] == 's')) {
                    outputQueue[outputQueueIndex++] = operatorStack[--operatorStackIndex];
                }
                operatorStack[operatorStackIndex++] = expression[i];
            }
            else if (expression[i] == '*' || expression[i] == '/') {
                while (operatorStackIndex > 0 &&
                    (operatorStack[operatorStackIndex - 1] == '*' ||
                        operatorStack[operatorStackIndex - 1] == '/' ||
                        operatorStack[operatorStackIndex - 1] == '^' ||
                        operatorStack[operatorStackIndex - 1] == 's')) {
                    outputQueue[outputQueueIndex++] = operatorStack[--operatorStackIndex];
                }
                operatorStack[operatorStackIndex++] = expression[i];
            }
            else if (expression[i] == '^' || expression[i] == '#') {
                while (operatorStackIndex > 0 &&
                    (operatorStack[operatorStackIndex - 1] == '^' ||
                        operatorStack[operatorStackIndex - 1] == '#')) {
                    outputQueue[outputQueueIndex++] = operatorStack[--operatorStackIndex];
                }
                operatorStack[operatorStackIndex++] = expression[i];
            }
            else if (expression[i] == '(') {
                operatorStack[operatorStackIndex++] = expression[i];
            }
            else if (expression[i] == ')') {
                while (operatorStackIndex > 0 && operatorStack[operatorStackIndex - 1] != '(') {
                    outputQueue[outputQueueIndex++] = operatorStack[--operatorStackIndex];
                }
                if (operatorStackIndex == 0) {
                    throw std::invalid_argument("Eroare paranteze nepotrivire");
                }
                operatorStackIndex--; 
            }
            else if (expression[i] == '[') {
                operatorStack[operatorStackIndex++] = expression[i];
            }
            else if (expression[i] == ']') {
                while (operatorStackIndex > 0 && operatorStack[operatorStackIndex - 1] != '[') {
                    outputQueue[outputQueueIndex++] = operatorStack[--operatorStackIndex];
                }
                if (operatorStackIndex == 0) {
                    throw std::invalid_argument("Eroare paranteze nepotrivire");
                }
                operatorStackIndex--; 
            }
            else {
                throw std::invalid_argument("Eroare de simbol nevalid");
            }
        }

        while (operatorStackIndex > 0) {
            if (operatorStack[operatorStackIndex - 1] == '(' || operatorStack[operatorStackIndex - 1] == ')' || operatorStack[operatorStackIndex - 1] == '[' || operatorStack[operatorStackIndex - 1] == ']') {
                throw std::invalid_argument("Eroare paranteze nepotrivire");
            }
            outputQueue[outputQueueIndex++] = operatorStack[--operatorStackIndex];
        }

        double operandStack[MAX_EXPRESSION_LENGTH];
        int operandStackIndex = 0;

        for (int i = 0; i < outputQueueIndex; i++) {
            if (outputQueue[i] == '+' || outputQueue[i] == '-' || outputQueue[i] == '*' || outputQueue[i] == '/' || outputQueue[i] == '^' || outputQueue[i] == '#') {
                if (operandStackIndex < 2) {
                    throw std::invalid_argument("Eroare expresie invalida");
                }
                double b = operandStack[--operandStackIndex];
                double a = operandStack[--operandStackIndex];
                if (outputQueue[i] == '+') {
                    operandStack[operandStackIndex++] = add(a, b);
                }
                else if (outputQueue[i] == '-') {
                    operandStack[operandStackIndex++] = subtract(a, b);
                }
                else if (outputQueue[i] == '*') {
                    operandStack[operandStackIndex++] = multiply(a, b);
                }
                else if (outputQueue[i] == '/') {
                    operandStack[operandStackIndex++] = divide(a, b);
                }
                else if (outputQueue[i] == '^') {
                    operandStack[operandStackIndex++] = exponentiate(a, b);
                }
                else if (outputQueue[i] == '#') {
                    operandStack[operandStackIndex++] = nthRoot(a, b);
                }
            }
            else {
                operandStack[operandStackIndex++] = outputQueue[i];
            }
        }

        if (operandStackIndex != 1) {
            throw std::invalid_argument("eroare expresie invalida");
        }
       
        return operandStack[0];
    }
};

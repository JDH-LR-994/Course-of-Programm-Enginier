//
// Created by jdh99 on 3/18/2025.
//

#ifndef TASKFUNC_HPP
#define TASKFUNC_HPP
#pragma once
#include "StackArray.hpp"


class TaskFunc {
public:
    static bool checkBalanceBrackets(const char *text, int maxDeep);
    static void getPostfixFromInfix(const char* infix, char* postfix, long long stackSize);

private:
    static int precedence(char op);
};

inline bool TaskFunc::checkBalanceBrackets(const char *text, const int maxDeep) {
    StackArray<char> stack(maxDeep);

    for (size_t i = 0; text[i] != '\0'; ++i) {
        char currentChar = text[i];

        if (currentChar == '(' || currentChar == '{' || currentChar == '[') {
            try {
                stack.push(currentChar);
            } catch (StackOverflow &) {
                return false;
            }
        } else if ((currentChar == ')' && !stack.isEmpty() && stack.pop() != '(') ||
                   (currentChar == '}' && !stack.isEmpty() && stack.pop() != '{') ||
                   (currentChar == ']' && !stack.isEmpty() && stack.pop() != '[')) {
            return false;
        }
    }

    return stack.isEmpty();
}

inline void TaskFunc::getPostfixFromInfix(const char *infix, char *postfix, long long stackSize) {
    StackArray<char> operators(stackSize);
    size_t postfixIndex = 0;

    for (size_t i = 0; infix[i] != '\0'; ++i) {
        char ch = infix[i];

        if (isdigit(ch)) {
            postfix[postfixIndex++] = ch; // Добавляем цифру в postfix
        } else if (ch == '(') {
            operators.push(ch); // Помещаем открывающую скобку в стек
        } else if (ch == ')') {
            // Извлекаем операторы из стека до открывающей скобки
            while (!operators.isEmpty() && operators.pop() != '(') {
                postfix[postfixIndex++] = operators.pop();
            }
        } else {
            // Обрабатываем операторы
            while (!operators.isEmpty() && precedence(operators.pop()) >= precedence(ch)) {
                postfix[postfixIndex++] = operators.pop();
            }
            operators.push(ch); // Помещаем текущий оператор в стек
        }
    }

    // Извлекаем оставшиеся операторы из стека
    while (!operators.isEmpty()) {
        postfix[postfixIndex++] = operators.pop();
    }

    postfix[postfixIndex] = '\0'; // Завершаем строку postfix
}

inline int TaskFunc::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


#endif //TASKFUNC_HPP

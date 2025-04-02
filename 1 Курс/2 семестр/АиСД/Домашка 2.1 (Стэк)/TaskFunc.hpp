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


#endif //TASKFUNC_HPP

#include "solution.hpp"



bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_letter(char c) {
    return (c >= 'a' && c <= 'f') || c == 'x' || c == 'y' || c == 'z';
}

bool is_integer_without_sign(const std::string &str, std::size_t &pos) {
    if (pos >= str.size() || !is_digit(str[pos])) return false;
    pos++;
    if (pos < str.size() && is_digit(str[pos])) {
        return is_integer_without_sign(str, pos);
    }
    return true;
}

bool is_identifier(const std::string &str, std::size_t &pos) {
    if (pos >= str.size() || !is_letter(str[pos])) return false;
    pos++;
    return true;
}


bool is_term(const std::string &str, std::size_t &pos) {
    if (!is_factor(str, pos)) return false;
    if (pos < str.size() && (str[pos] == '*' || str[pos] == '/')) {
        pos++;
        return is_term(str, pos);
    }
    return true;
}


bool is_factor(const std::string &str, std::size_t &pos) {
    if (is_integer_without_sign(str, pos)) return true;
    if (is_identifier(str, pos)) return true;
    if (pos < str.size() && str[pos] == '(') {
        pos++;
        if (!is_expression(str, pos)) return false;
        if (pos >= str.size() || str[pos] != ')') return false;
        pos++;
        return true;
    }
    return false;
}

bool is_expression(const std::string &str, std::size_t &pos) {
    if (!is_term(str, pos)) return false;
    if (pos < str.size() && (str[pos] == '+' || str[pos] == '-')) {
        pos++;
        return is_expression(str, pos);
    }
    return true;
}

bool check_expression(const std::string &str) {
    std::size_t pos = 0;
    bool result = is_expression(str, pos);
    return result && pos == str.size();
}
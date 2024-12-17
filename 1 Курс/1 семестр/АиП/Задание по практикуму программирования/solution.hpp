#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <iostream>

bool is_digit(char c);
bool is_letter(char c);
bool is_integer_without_sign(const std::string &str, std::size_t &pos);
bool is_identifier(const std::string &str, std::size_t &pos);
bool is_term(const std::string &str, std::size_t &pos);
bool is_factor(const std::string &str, std::size_t &pos);
bool is_expression(const std::string &str, std::size_t &pos);
bool check_expression(const std::string &str);

#endif  // SOLUTION_HPP
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "TermStructure.h"
#include <iostream>

int main() {
    double t1 = 1; double r_t1 = 0.05; double d_t1 = term_structure_discount_factor_from_yield(r_t1, t1);
    std::cout << " a " << t1 << " period spot rate of " << r_t1
        << " corresponds to a discount factor of " << d_t1 << std::endl;
    double t2 = 2; double d_t2 = 0.9;
    double r_t2 = term_structure_yield_from_discount_factor(d_t2, t2);
    std::cout << " a " << t2 << " period discount factor of " << d_t2
        << " corresponds to a spot rate of " << r_t2 << std::endl;
    std::cout << " the forward rate between " << t1 << " and " << t2
        << " is " << term_structure_forward_rate_from_discount_factors(d_t1, d_t2, t2-t1)
        << " using discount factors " << std::endl;
    std::cout << " and is " << term_structure_forward_rate_from_yields(r_t1, r_t2, t1, t2)
        << " using yields " << std::endl;
    return 0;
}


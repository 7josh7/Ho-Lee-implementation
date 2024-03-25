#ifndef TERMSTRUCTURE_H
#define TERMSTRUCTURE_H

#include <cmath>

// Declares a namespace to encapsulate the functions, if they belong to a namespace in your project
// using namespace std; // Typically, using directives are not recommended in header files.

// Function declarations
double term_structure_yield_from_discount_factor(const double& dt, const double& t);  // constant might add up speed
double term_structure_discount_factor_from_yield(const double& r, const double& t);
double term_structure_forward_rate_from_discount_factors(const double& dt_1, const double& dt_2, const double& time);
double term_structure_forward_rate_from_yields(const double& r_t1, const double& r_t2, const double& t1, const double& t2);

#endif // TERMSTRUCTURE_H

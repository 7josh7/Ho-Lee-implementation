#include "TermStructure.h"
#include<cmath>
using namespace std;

double term_structure_yield_from_discount_factor(const double& dt, const double& t) {
	return(-log(dt) / t);
}
double term_structure_discount_factor_from_yield(const double& r, const double& t) {
	return exp( -r * t);
};
double term_structure_forward_rate_from_discount_factors(const double& dt_1, const double& dt_2, const double& time) {
	return(log(dt_1 / dt_2)) / time;
};
double term_structure_forward_rate_from_yields(const double& r_t1, const double& r_t2,
	const double& t1, const double& t2) {
	return r_t2 * t2 / (t2-t1) - r_t1 * t1 / (t2-t1);
};



// BlackScholes.cpp
#include "BlackScholes.h"
#include <cmath>
DFinMath::DStat myDStat;

void BlackScholes::validateInputs(double K, double sigma, double time) {
    if (K <= 0) throw std::invalid_argument("Strike price must be greater than zero.");
    if (sigma <= 0) throw std::invalid_argument("Volatility must be greater than zero.");
    if (time <= 0) throw std::invalid_argument("Time to maturity must be greater than zero.");
}

// Setter methods
void BlackScholes::setS(double S) {
    S_ = S;
    calculate_d1_d2();
    calculate_n_d1_n_d2();
}
void BlackScholes::setK(double K) {
    if (K <= 0) throw std::invalid_argument("Strike price must be greater than zero.");
    K_ = K;
    calculate_d1_d2();
    calculate_n_d1_n_d2();
}
void BlackScholes::setR(double r) {
    r_ = r;
    calculate_d1_d2();
    calculate_n_d1_n_d2();
}
void BlackScholes::setSigma(double sigma) {
    if (sigma <= 0) throw std::invalid_argument("Volatility must be greater than zero.");
    sigma_ = sigma;
    calculate_d1_d2();
    calculate_n_d1_n_d2();
}
void BlackScholes::setTime(double time) {
    if (time <= 0) throw std::invalid_argument("Time to maturity must be greater than zero.");
    time_ = time;
    time_sqrt = std::sqrt(time_);
    calculate_d1_d2();
    calculate_n_d1_n_d2();
}

// Getter methods
void BlackScholes::calculate_d1_d2() {
    d1 = (std::log(S_ / K_) + r_ * time_ + 0.5 * sigma_ * sigma_ * time_) / (sigma_ * time_sqrt);
    d2 = d1 - (sigma_ * time_sqrt);
}
double BlackScholes::gamma() const {
    return std::exp(-y_ * time_) * myDStat.NormDensity(d1) / (S_ * sigma_ * time_sqrt);
}
double BlackScholes::vega() const {
    return S_ * std::exp(-y_ * time_) * myDStat.NormDensity(d1) * time_sqrt;
}
double BlackScholes::theta() const {
	return -S_ * sigma_ * std::exp(-y_ * time_) * myDStat.NormDensity(d1) / (2 * time_sqrt) + y_ * S_ * std::exp(-y_ * time_) * n_d1 - r_ * K_ * std::exp(-r_ * time_) * n_d2;
}
// Getter methods CallOption
double CallOption::option_price() {
    return S_ * std::exp(-y_ * time_) * n_d1 - K_ * std::exp(-r_ * time_) * n_d2;
}
void CallOption::calculate_n_d1_n_d2(){
    n_d1 = myDStat.NormDist(d1);
    n_d2 = myDStat.NormDist(d2);
}

double CallOption::delta(){
    return n_d1 * exp(-y_ * time_);
}
double CallOption::rho(){
    return K_ * time_ * exp(-r_ * time_) * n_d2;
}



// Getter methods PutOption
double PutOption::option_price() {
    return K_ * std::exp(-r_ * time_) * n_d2 - S_ * std::exp(-y_ * time_) * n_d1;
}
void PutOption::calculate_n_d1_n_d2(){
    n_d1 = myDStat.NormDist(-d1);
    n_d2 = myDStat.NormDist(-d2);
}
double PutOption::delta(){
    return -n_d1 * exp(-y_ * time_);
}
double PutOption::rho(){
    return -K_ * time_ * exp(-r_ * time_) * n_d2;
}



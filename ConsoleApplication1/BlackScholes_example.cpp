//#include <iostream>
//#include "BlackScholes.h"
//#include <nana/gui.hpp>
//
//int main() {
//
//    // Define parameters for the options
//    double S = 50;    // Underlying stock price
//    double K = 50;    // Strike price
//    double r = 0.1;     // Risk-free rate
//    double sigma = 0.3;  // Volatility
//    double time = 0.5;   // Time to maturity (in years)
//
//    // Create a CallOption instance
//    CallOption call(S, K, r, sigma, time);
//    // Create a PutOption instance
//    PutOption put(S, K, r, sigma, time);
//
//    // Calculate and print the prices
//    std::cout << "Call Option Price: " << call.option_price() << std::endl;
//    std::cout << "Put Option Price: " << put.option_price() << std::endl;
//
//    return 0;
//}
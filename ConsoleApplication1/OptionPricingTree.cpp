#include "OptionPricingTree.h"

OptionPricingTree::OptionPricingTree(double S, double K, double r, double sigma, double t, int steps)
    : S(S), K(K), r(r), sigma(sigma), t(t), steps(steps) {
}

void OptionPricingTree::calculate_parameters() {
    R = exp(r * (t / steps));        // Interest rate for each step
    Rinv = 1.0 / R;                  // Inverse of interest rate
    u = exp(sigma * sqrt(t / steps)); // Up movement factor
    uu = u * u;
    d = 1.0 / u;                     // Down movement factor
    p_up = (R - d) / (u - d);        // Risk-neutral up probability
    p_down = 1.0 - p_up;             // Risk-neutral down probability
}

double OptionPricingTree::price_call_european_binomial() {
    calculate_parameters();
    std::vector<double> prices(steps + 1); // Price of underlying
    prices[0] = S * pow(d, steps);         // Fill in the endnodes
    for (int i = 1; i <= steps; ++i) {
        prices[i] = uu * prices[i - 1];
    }

    std::vector<double> call_values(steps + 1); // Value of corresponding call
    for (int i = 0; i <= steps; ++i) {
        call_values[i] = std::max(0.0, prices[i] - K); // Call payoffs at maturity
    }

    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
        }
    }

    return call_values[0];
}

double OptionPricingTree::price_call_american_binomial() {
std::vector<double> prices(steps + 1); // Price of underlying
prices[0] = S * pow(d, steps);         // Fill in the endnodes
for (int i = 1; i <= steps; ++i) {
    prices[i] = uu * prices[i - 1];
}

std::vector<double> call_values(steps + 1); // Value of corresponding call
for (int i = 0; i <= steps; ++i) {
    call_values[i] = std::max(0.0, prices[i] - K); // Call payoffs at maturity
}

for (int step = steps - 1; step >= 0; --step) {
    for (int i = 0; i <= step; ++i) {
        call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
        prices[i] = d * prices[i + 1];
        call_values[i] = std::max(call_values[i], prices[i] - K); //check for exercise
        // note that holding the option is always preferable to exercising it early because you maintain the option's time value.
        // The value of the option can increase further if the underlying stock price rises.
    }
}

return call_values[0];
}



//-----------------------------------------bond--------------------------------------------------------------------------------------
BondOptionPricingTree::BondOptionPricingTree(double S, double K, double r, double sigma, double t, int steps,
    double bond_maturity, double M, double maturity_payment)
    : OptionPricingTree(S, K, r, sigma, t, steps), bond_maturity(bond_maturity), M(M), maturity_payment(maturity_payment) {
}

void BondOptionPricingTree::calculate_parameters() {
    // Custom parameter calculations for bond option pricing
    delta_t = bond_maturity / steps;

    u = exp(S * sqrt(delta_t));    // Up movement factor
    uu = u * u;
    d = 1.0 / u;                                 // Down movement factor
    p_up = (exp(M * delta_t) - d) / (u - d); // Risk-neutral up probability
    p_down = 1.0 - p_up;                         // Risk-neutral down probability
 
    R = exp(r * (bond_maturity / steps));        // Interest rate for each step
    Rinv = 1.0 / R;                              // Inverse of interest rate
}

double BondOptionPricingTree::bond_option_price_call_zero_american_rendleman_bartter() {
    calculate_parameters();

    //final vector of tree of interest rate
    std::vector<double> r(steps + 1);
    r[0] = R * pow(d, steps);
    double uu = u * u;
    for (int i = 1; i <= steps; ++i) {
        r[i] = r[i - 1] * uu;
    }

    //final vector of tree of bond
    std::vector<double> P(steps + 1);
    for (int i = 0; i <= steps; ++i) {
        P[i] = maturity_payment;
    }

    //update tree of interest rate and bound
    int no_call_steps = int(steps * t / bond_maturity);
    for (int curr_step = steps; curr_step > no_call_steps; --curr_step) {
        for (int i = 0; i < curr_step; ++i) {
            r[i] = r[i] * u;
            P[i] = exp(-r[i] * delta_t) * (p_down * P[i] + p_up * P[i + 1]);
        }
    }

    //final vector of tree of option
    std::vector<double> C(no_call_steps + 1);
    for (int i = 0; i <= no_call_steps; ++i) {
        C[i] = std::max(0.0, P[i] - K);
    }
    //update tree of option
    for (int curr_step = no_call_steps; curr_step > 0; --curr_step) {
        for (int i = 0; i < curr_step; i++) {
            r[i] = r[i] * u;
            P[i] = exp(-r[i] * delta_t) * (p_down * P[i] + p_up * P[i + 1]);
            C[i] = std::max(P[i] - K, exp(-r[i] * delta_t) * (p_up * C[i + 1] + p_down * C[i]));
        }
    }
    return C[0];
}



#include <iostream>
#include "OptionPricingTree.h"

int main() {
    double S = 0.15;    // Spot price
    double K = 950;    // Exercise price
    double M = 0.05;
    double r = 0.1;     // Interest rate
    double sigma = 0.2;  // Volatility
    double t = 4.0;      // Time to maturity of option
    double bond_maturity = 5;
    double maturity_payment = 1000;
    int steps = 1000;     // Number of steps in binomial tree

    BondOptionPricingTree bondOption(S, K, r, sigma, t, steps, bond_maturity, M, maturity_payment);
    double call_price = bondOption.bond_option_price_call_zero_american_rendleman_bartter();

    std::cout << "European Call Option Price: " << call_price << std::endl;

    return 0;
}

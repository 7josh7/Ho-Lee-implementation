#ifndef OPTION_PRICING_H
#define OPTION_PRICING_H

#include <cmath>
#include <algorithm>
#include <vector>

class OptionPricingTree {
protected:
    double S;      // Spot price
    double K;      // Exercise price
    double r;      // Interest rate
    double sigma;  // Volatility
    double t;      // Time to maturity
    int steps;     // Number of steps in binomial tree
    double R;      // Interest rate for each step (or current short interest rate if calculating bondoption)
    double Rinv;   // Inverse of interest rate
    double u;      // Up movement factor
    double uu;
    double d;      // Down movement factor
    double p_up;   // Risk-neutral up probability
    double p_down; // Risk-neutral down probability
    virtual void calculate_parameters();

public:
    OptionPricingTree(double S, double K, double r, double sigma, double t, int steps);
    double price_call_european_binomial();
    double price_call_american_binomial();
};



class BondOptionPricingTree : public OptionPricingTree {
protected:
    double bond_maturity;  // Time to maturity for underlying bond
    double M;              // Term structure parameters
    double delta_t;
    double maturity_payment;

    void calculate_parameters() override;

public:
    BondOptionPricingTree(double S, double K, double r, double sigma, double t, int steps,double bond_maturity, double M, double maturity_payment);
    double bond_option_price_call_zero_american_rendleman_bartter();
};

#endif // OPTION_PRICING_H

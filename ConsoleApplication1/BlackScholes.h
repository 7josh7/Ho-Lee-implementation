// BlackScholes.h
#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

#include "DStat.h" // Include the header for statistical functions
#include <cmath> // Include the header for mathematical functions
#include <stdexcept>  // Include standard exceptions

class BlackScholes{
protected:
    double S_;   // spot (underlying) price
    double K_;   // strike (exercise) price
    double r_;        // interest rate, can be double or TermStructure
    double y_;  // yield
    double sigma_; // volatility
    double time_; // time to maturity
    double time_sqrt; // square root of time to maturity
    double d1; // d1    
    double d2; // d2    
    double n_d1; // standard normal cumulative distribution function
    double n_d2; // standard normal cumulative distribution function
    void validateInputs(double K, double sigma, double time);
public:
    // Constructor
    BlackScholes(const double& S = 50, const double& K = 50, const double& r = 0.05, const double& sigma = 0.2, const double& time = 1, const double& yield = 0)
        : S_(S), K_(K), r_(r), sigma_(sigma), time_(time), y_(yield) {
        validateInputs(K, sigma, time);
        time_sqrt = std::sqrt(time_);
        calculate_d1_d2();
    }
    // Copy constructor
    BlackScholes(const BlackScholes& bs)
        : S_(bs.S_), K_(bs.K_), r_(bs.r_), sigma_(bs.sigma_), time_(bs.time_), time_sqrt(bs.time_sqrt), d1(bs.d1), d2(bs.d2), n_d1(bs.n_d1), n_d2(bs.n_d2), y_(bs.y_) {}

    // Destructor
    ~BlackScholes() {}

    // Pure virtual function for option price
    virtual double option_price() = 0;
    virtual void calculate_n_d1_n_d2() = 0;
    virtual double delta() = 0;
    virtual double rho() = 0;

    // Setter methods
    void calculate_d1_d2();
    void setS(double S);
    void setK(double K);
    void setR(double r);
    void setSigma(double sigma);
    void setTime(double time);

    // Getter methods
    double gamma() const;
    double vega() const;
    double theta() const;
};


class CallOption : public BlackScholes {
public:
    // Constructor for CallOption - initializes base class BlackScholes with passed parameters
    CallOption(const double& S = 50, const double& K = 50, const double& r = 0.05, const double& sigma = 0.2, const double& time = 1, const double& yield = 0)
        : BlackScholes(S, K, r, sigma, time, yield) {
        calculate_n_d1_n_d2();
    }

    // Destructor for CallOption - currently does nothing but could handle resource cleanup if needed
    ~CallOption() {}


    void calculate_n_d1_n_d2() override;
    double option_price();
    double delta() override;
    double rho() override;
};

class PutOption : public BlackScholes {
public:
    // Constructor for PutOption - initializes base class BlackScholes with passed parameters
    PutOption(const double& S = 50, const double& K = 50, const double& r = 0.05, const double& sigma = 0.2, const double& time = 1, const double& yield = 0)
        : BlackScholes(S, K, r, sigma, time, yield) {
        calculate_n_d1_n_d2();
    }

    // Destructor for PutOption - currently does nothing but could handle resource cleanup if needed
    ~PutOption() {}
    void calculate_n_d1_n_d2() override;
    double option_price();
    double delta();
    double rho();
};


#endif // BLACK_SCHOLES_H

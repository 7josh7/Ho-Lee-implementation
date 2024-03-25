#ifndef TERM_STRUCTURE_H
#define TERM_STRUCTURE_H

#include <vector>

namespace financial_math {

    class TermStructure {
    public:
        struct NelsonSiegelParams {
            double beta0;
            double beta1;
            double beta2;
            double tau;

            NelsonSiegelParams(double b0, double b1, double b2, double t)
                : beta0(b0), beta1(b1), beta2(b2), tau(t) {}
        };
        struct Bond {
            double price;
            double faceValue;
            double couponRate;
            int frequency;
            double maturity;
        };

        static double yieldFromDiscountFactor(const double& d_t, const double& t);
        static double discountFactorFromYield(const double& r, const double& t);
        static double forwardRateFromDiscountFactors(const double& d_t1, const double& d_t2, const double& time);
        static double forwardRateFromYields(const double& r_t1, const double& r_t2, const double& t1, const double& t2);
        static double nelsonSiegelSpotRate(double t, const NelsonSiegelParams& params);
        static double nelsonSiegelDiscountFactor(double t, const NelsonSiegelParams& params);
        static std::vector<double> bootstrapYieldCurve(const std::vector<Bond>& bonds);
    };

} // namespace financial_math

#endif // TERM_STRUCTURE_H
